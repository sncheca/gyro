/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

//convert a soundfield into stereo. This won't sound as good as binaural, but it's good for quick checking and ABing.

#include "c74_min.h"
#include "ambisonics/ambisonic_binaural_decoder.h"
#include "audio_buffer_conversion.h"

#include "dsp/fft_manager.h"
#include "dsp/partitioned_fft_filter.h"
#include "dsp/sh_hrir_creator.h"
#include "utils/wav.h"

using namespace c74::min;
using namespace vraudio; //TODO clean these (after everything else compiles)

std::ifstream filenameToIstream(string s){
    std::ifstream ifilestream;
    ifilestream.open(s, std::ifstream::in);  //TODO need safety checking that the file opened!
    return ifilestream;
}

class binauralDecoder : public object<binauralDecoder>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumIns;
    const float kSampleRate = c74::max::sys_getsr(); //not actually sure whether to init this here or in the constructor
    const int kBlockSize = c74::max::sys_getblksize();
    AmbisonicBinauralDecoder binaural_decoder;
    
    std::vector< std::unique_ptr<inlet<>> >    m_inlets; //note that this must be called m_inputs!
public:
    MIN_DESCRIPTION    { "Encode a mono point source sound to ambisonic sound field. Make this more precise" };
    MIN_TAGS        { "audio, sampling" };
    MIN_AUTHOR        { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };


    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    binauralDecoder(const atoms& args = {})
        : kAmbisonicOrder(args[0]),
          kNumIns((kAmbisonicOrder+1)*(kAmbisonicOrder+1)) { //TODO turn this into a function. see hoa_rotator.cc for GetNumNthOrder
        
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
        
        //build the decoder object
        string fileName = "mySadie/sh_hrir_order_" + std::to_string(kAmbisonicOrder) + ".wav";      //find the wav file needed to construct the hrir
        std::ifstream ifs = filenameToIstream(fileName);
        Resampler resampler;
        unique_ptr<vraudio::AudioBuffer> sh_hrirs = CreateShHrirsFromWav(*(vraudio::Wav::CreateOrNull(&ifs)), kSampleRate, &resampler);
        vraudio::FftManager fftManager(kBlockSize);
        binaural_decoder = AmbisonicBinauralDecoder(*sh_hrirs , kBlockSize, &fftManager);
        
    }
    outlet<>  out1    { this, "(signal) Stereo Left", "signal" };
    outlet<>  out2    { this, "(signal) Stereo Right", "signal" };

    void operator()(audio_bundle input, audio_bundle output) {
 
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumIns, nFrames);      // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(2, nFrames);           // resonance-style audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);                            // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
//        StereoFromSoundfield(r_inputAudioBuffer, &r_outputAudioBuffer); //convert the soundfield into stereo using mid-side
        binaural_decoder.Process(r_inputAudioBuffer, &r_outputAudioBuffer);
        
        Res2Min(r_outputAudioBuffer, &output);                    // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(binauralDecoder);
