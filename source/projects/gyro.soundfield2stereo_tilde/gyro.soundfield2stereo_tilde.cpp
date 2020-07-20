/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

//convert a soundfield into stereo. This won't sound as good as binaural, but it's good for quick checking and ABing.

#include "c74_min.h"
#include "ambisonics/stereo_from_soundfield_converter.h"
#include "audio_buffer_conversion.h"

#include "dsp/gain.h"

using namespace c74::min;

class soundfield2stereo : public object<soundfield2stereo>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumIns;
    std::vector< std::unique_ptr<inlet<>> >    g_inlets; //note that this must be called m_inputs!
public:
    MIN_DESCRIPTION    { "Encode a mono point source sound to ambisonic sound field. Make this more precise" };
    MIN_TAGS        { "audio, sampling" };
    MIN_AUTHOR        { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };


    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    soundfield2stereo(const atoms& args = {}):kAmbisonicOrder(args[0]), kNumIns((kAmbisonicOrder+1)*(kAmbisonicOrder+1)) { //TODO turn this into a function. see hoa_rotator.cc for GetNumNthOrder
        if (args.empty()){
            error("Argument required. Please include the ambisonic order.");
        } else if(int(args[0]) > 3 || int(args[0]) < 1){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        auto inlet_count = kNumIns;

        for (auto i=0; i < inlet_count; ++i) {
            //TODO the channel number should be in the assist message. String nonsense.
            auto an_inlet = std::make_unique<inlet<>>(this, "(signal) Channel", "signal");
            g_inlets.push_back( std::move(an_inlet) );
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
