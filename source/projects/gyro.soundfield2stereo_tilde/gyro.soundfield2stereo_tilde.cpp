/// @file
///    @ingroup     gyro
///    @copyright    Copyright 2020 Sofia Checa
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

// Copyright 2020 Sofia Checa
// This work was funded by Yale Department of Music // Yale CCAM // Yale Blended Reality

//convert a soundfield into stereo. This will sound much worse than binaural, but it's good for ABing and quick checking.

#include "c74_min.h"
#include "ambisonics/stereo_from_soundfield_converter.h"
#include "ambisonics/utils.h"
#include "audio_buffer_conversion.h"

#include "dsp/gain.h"

using namespace c74::min;

class soundfield2stereo : public object<soundfield2stereo>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumIns;
    std::vector< std::unique_ptr<inlet<>> >    g_inlets;
    
public:
    MIN_DESCRIPTION    { "Decode an ambisonic soundfield to stereo" };
    MIN_TAGS        { "gyro, binaural, ambisonics, audio" };
    MIN_AUTHOR        { "Sofia Checa" };
    MIN_RELATED        { "gyro.encoder~, gyro.binauralDecoder~, gyro.speakerDecoder~, gyro.rotator~, gyro.thru~" };


    // constructor that allows for number of outlets to be defined by the ambisonic order argument.
    soundfield2stereo(const atoms& args = {}):
        kAmbisonicOrder(args.empty() ? 1: int(args[0])),    //set the default ambisonic order to 1 if there are no arguments
        kNumIns(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder))
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
        
    }
    outlet<>  out1    { this, "(signal) Stereo Left", "signal" };
    outlet<>  out2    { this, "(signal) Stereo Right", "signal" };

    void operator()(audio_bundle input, audio_bundle output) {
 
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumIns, nFrames);      // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(2, nFrames);           // resonance-style audio buffer for output
        pita::Min2Res(input, &r_inputAudioBuffer);                            // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
        StereoFromSoundfield(r_inputAudioBuffer, &r_outputAudioBuffer); //convert the soundfield into stereo using mid-side
        
        pita::Res2Min(r_outputAudioBuffer, &output);                    // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(soundfield2stereo);
