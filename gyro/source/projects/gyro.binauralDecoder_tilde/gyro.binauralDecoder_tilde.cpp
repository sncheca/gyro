/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

//convert a soundfield into stereo. This won't sound as good as binaural, but it's good for quick checking and ABing.

#include "c74_min.h"
#include "ambisonics/ambisonic_binaural_decoder.h"
#include "audio_buffer_conversion.h"

#include "dsp/sh_hrir_creator.h"
#include "utils/wav.h"

// these are already included in the above, but just in case
#include "dsp/fft_manager.h"
#include "dsp/partitioned_fft_filter.h"
#include "third_party/pffft/pffft.h"

using namespace c74::min;
//using namespace vraudio; //TODO clean these (after everything else compiles)

//std::ifstream filenameToIstream(const string s){
//    std::ifstream ifs;
//    ifs.open(s, std::ifstream::in);  //TODO need safety checking that the file opened!
//    if(ifs.good()){
//        return ifs;
//    } else {
//        error("Unable to open file" + s);
//        exit(3);
//    }
//}

class binauralDecoder : public object<binauralDecoder>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumIns;
    const float kSampleRate = c74::max::sys_getsr();
    const size_t kBlockSize = c74::max::sys_getblksize();

    //convert the hrir wav file into something we can use. TODO move more of this into the above function, depending on how we use it.
    std::ifstream ifs;
    std::unique_ptr<const vraudio::Wav> wav;
    
    vraudio::Resampler resampler; //use default constructor
    unique_ptr<vraudio::AudioBuffer> my_sh_hrirs;
    
    vraudio::FftManager fftManager; //will be initialised in initialisation list below
    vraudio::AmbisonicBinauralDecoder binaural_decoder; //will be initialised in initialisation list below

    std::vector< std::unique_ptr<inlet<>> >    m_inlets; //note that this must be called m_inputs!
public:
    MIN_DESCRIPTION    { "binaural decoder" };
    MIN_TAGS           { "audio, sampling" };
    MIN_AUTHOR         { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };


    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    binauralDecoder(const atoms& args = {})
      : kAmbisonicOrder(args[0]),
        kNumIns((kAmbisonicOrder+1)*(kAmbisonicOrder+1)),
        ifs(filenameToIstream("../../resonance_audio/third_party/SADIE_hrtf_database/WAV/Subject_002/SH/sh_hrir_order_" + std::to_string(kAmbisonicOrder) + ".wav")),
        wav(vraudio::Wav::CreateOrNull(&ifs)),
        my_sh_hrirs(CreateShHrirsFromWav(*wav, kSampleRate, &resampler)),
        fftManager(kBlockSize), //note that this argument must be of type size_t, since the constructor is explicit. Do not try to cast inside the parentheses. This could lead to unintended consequences if you do not manage parentheses correctly, due to the so-called "Most Vexing Parse"
        binaural_decoder(*my_sh_hrirs, kBlockSize, &fftManager){ //TODO turn this into a function. see hoa_rotator.cc for GetNumNthOrder
        
        //inlet handling
        if (args.empty()){
            error("Argument required. Please include the ambisonic order.");
        } else if(int(args[0]) > 3 || int(args[0]) < 1){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        auto inlet_count = kNumIns;

        for (auto i=0; i < inlet_count; ++i) {
            //TODO the channel number should be in the assist message. String nonsense.
            auto an_inlet = std::make_unique<inlet<>>(this, "(signal) Channel", "signal");
            m_inlets.push_back( std::move(an_inlet) );
        }
    }
    
    outlet<>  out1    { this, "(signal) Stereo Left", "signal" };
    outlet<>  out2    { this, "(signal) Stereo Right", "signal" };
    
    c74::min::function stringToStream = MIN_FUNCTION {
        std::ifstream ifs;
        ifs.open(s, std::ifstream::in);  //TODO need safety checking that the file opened!
        if(ifs.good()){
            
//            return ifs;
        } else {
            error("Unable to open file" + s);
            exit(3);
        }
        return {};
    }

    void operator()(audio_bundle input, audio_bundle output) {
 
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumIns, nFrames);      // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(2, nFrames);           // resonance-style audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);                            // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
//        StereoFromSoundfield(r_inputAudioBuffer, &r_outputAudioBuffer); //convert the soundfield into stereo using mid-side
        binaural_decoder.Process(r_inputAudioBuffer, &r_outputAudioBuffer); //decode the buffer!
        
        Res2Min(r_outputAudioBuffer, &output);                    // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(binauralDecoder);
