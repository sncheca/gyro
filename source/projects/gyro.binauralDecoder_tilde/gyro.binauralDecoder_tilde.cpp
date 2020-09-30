/// @file
///    @ingroup     gyro
///    @copyright    Copyright 2020 Sofia Checa
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

// Copyright 2020 Sofia Checa
// This work was funded by Yale Department of Music // Yale CCAM // Yale Blended Reality

//binaurally render a soundfield, using HRTFs from the SADIE-I HRTF database: https://www.york.ac.uk/sadie-project/database_old.html

#include "c74_min.h"
#include "ambisonics/ambisonic_binaural_decoder.h"
#include "ambisonics/utils.h"
#include "audio_buffer_conversion.h"

#include "dsp/sh_hrir_creator.h"
#include "utils/wav.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace c74::min;
//note that the vraudio namespace is used for Resonance objects. I do not "use" the vraudio namespace so that is clear to the viewer where these objects come from

// leaving this in for readers. This is an alternate approach to getting SHHRIR data. There are two ways to create spherical harmonic encoded hrirs. You can create them from wav or asset files. Both of those are generated by an external scripts.

//std::ifstream filenameToIstream(const std::string s){
//    std::ifstream ifs;
//    ifs.open(s, std::ifstream::in);  //TODO need safety checking that the file opened! And must throw / catch exception in the constructor!
//    if(ifs.good()){
//        return ifs;
//    } else {
//        error("Unable to open file" + s);
//        exit(3);
//    }
//}

// given a certain ambisonic order, use the sadie ambi-encoded wave files to generate an AudioBuffer containing the appropriate HRIRs.
//unique_ptr<vraudio::AudioBuffer> wav2HRIR(const int k, const float sr){
//    path p(std::string("sh_hrir_order_") + std::to_string(k) + std::string(".wav")); //The path function lets us tap into the file preferences of Max. See c74_min_path.h
//    std::ifstream ifs((filenameToIstream(std::string(p))));
//    unique_ptr<const vraudio::Wav> wav(vraudio::Wav::CreateOrNull(&ifs));
//    vraudio::Resampler resampler;
//    return vraudio::CreateShHrirsFromWav(*wav, sr, &resampler);
//}

//given a certain ambisonic order, use the sadie assets to generate an AudioBuffer containing the appropriate HRIRs.
unique_ptr<vraudio::AudioBuffer> asset2SHHRIR(const int subject, const int order, const float sr){
    std::ostringstream convert;   // stream used for the conversion with appropriate zero padding
    convert << std::setw(3) << std::setfill('0') << subject;
    std::string subjectString = convert.str();
    
    std::string s("WAV/Subject_" + subjectString + "/SH/sh_hrir_order_" + std::to_string(order) + ".wav");
    vraudio::Resampler resampler;
    return vraudio::CreateShHrirsFromAssets(s, sr, &resampler);
}


class binauralDecoder : public object<binauralDecoder>, public vector_operator<> {
private:
    const int MAX_SUBJECT_ID = 20;
    //everything else will be initialised in the member initialisation lists in the constructor
    const int kAmbisonicOrder;
    const int kNumIns;
    vraudio::FftManager fftManager;

    std::vector< std::unique_ptr<inlet<>> >    g_inlets; //note that this must be called m_inputs!
    outlet<>  out1    { this, "(signal) Stereo Left", "signal" };
    outlet<>  out2    { this, "(signal) Stereo Right", "signal" };
    std::vector< std::unique_ptr<vraudio::AmbisonicBinauralDecoder> > binaural_decoders;
    
public:
    MIN_DESCRIPTION    { "Decode an ambisonic soundfield to binaural. Use argument to select ambisonic order. Ambisonic order 1 by default." };
    MIN_TAGS           { "gyro, binaural, ambisonics, audio" };
    MIN_AUTHOR         { "Sofia Checa" };
    MIN_RELATED        { "gyro.encoder~, gyro.speakerDecoder~, gyro.rotator~, gyro.soundfield2Stereo~, gyro.thru~" };
    
    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    binauralDecoder(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),    //set the default ambisonic order to 1 if there are no arguments
        kNumIns(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),
        fftManager(vector_size()) //vector_size is a member of base vector_operator class. Will be reset if/when dsp chain is compiled

    {
        
       /* Quoted from "constants_and_types.h": "Maximum Ambisonic order currently supported in vr audio is 3, equivalent to High
        Quality sound object rendering mode. This number is limited by a) number of
        HRIR data points used in the binaural renderer; b) size of the lookup table
        controlling the angular spread of a sound source in the Ambisonic Lookup
        Table class."

        Maximum Ambisonic order currently supported in vr audio is 5. I changed this value after generating hrir assets for 4th and 5th order binaural decoders. Gyro does not use the Ambisonic lookup table provided by Resonance.
        */
        if(!args.empty() && (int(args[0]) > 5 || int(args[0]) < 1)){
            error("This package currently only supports ambisonic orders 1 through 5.");
        }
        
        //inlet handling
        for (auto i=0; i < kNumIns; ++i) {
            g_inlets.push_back( std::make_unique<inlet<>>(this, "(signal) Soundfield Channel " + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
        }
        
        //populate the vector of binaural decoders
        for (auto i = 0; i<MAX_SUBJECT_ID; i++){
            const unique_ptr<vraudio::AudioBuffer> special_sh_hrirs(asset2SHHRIR(i+1, kAmbisonicOrder, samplerate())); //convert from 0-indexing to 1-indexing
            binaural_decoders.push_back( std::make_unique<vraudio::AmbisonicBinauralDecoder>(*special_sh_hrirs, vector_size(), &fftManager));
        }
    }

    attribute<int, threadsafe::no, limit::clamp> subjectID_attr {this, "HRIR Subject", 2,
        description{"Select an HRIR Subject to be used for the binaural decoding. Subject IDs range from 1 to 20."},
        range{1,MAX_SUBJECT_ID}
    };
    
    message<> setSubject {this, "subject", "set the SADIE-I HRTF Database Subject to be used for the binaural decoding.",
        MIN_FUNCTION{
            subjectID_attr = args[0];
            return{};
        }
    };
    
    void operator()(audio_bundle input, audio_bundle output) {

        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumIns, nFrames);      // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(2, nFrames);           // resonance-style audio buffer for output
        pita::Min2Res(input, &r_inputAudioBuffer);                            // transfer audio data from min-style audio_bundle to resonance-style audioBuffer

        //convert from 1-indexing to 0-indexing
        binaural_decoders.at(subjectID_attr - 1)->Process(r_inputAudioBuffer, &r_outputAudioBuffer);     //decode the buffer!

        pita::Res2Min(r_outputAudioBuffer, &output);                          // transfer audio data from resonance-style audioBuffer to min-style audio_bundle

    }
};

MIN_EXTERNAL(binauralDecoder);
