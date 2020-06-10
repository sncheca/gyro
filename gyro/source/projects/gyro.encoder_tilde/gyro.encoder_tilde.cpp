/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

//an ambisonic encoder that supports 1st, 2nd, and 3rd order ambisonics. 

#include "c74_min.h"
#include "ambisonics/ambisonic_codec_impl.h"
#include "ambisonics/ambisonic_codec.h"
#include "audio_buffer_conversion.h"

#include "ambisonics/associated_legendre_polynomials_generator.h"
#include "base/spherical_angle.h" //yes needed

using namespace c74::min;

class encoder : public object<encoder>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumOutputChannels;
    const int kNumSources;
    vraudio::SphericalAngle myAngle;
    inlet<>  in1     { this, "(signal) Channel 1", "signal" };
    inlet<>  angleIn { this, "(list) Numbers to specify angles in axis-angle", "list"}; //first number is side-to-side, second number is up-down
    std::vector< std::unique_ptr<outlet<>> >    m_outlets; //note that this must be called m_outputs!
    std::unique_ptr<vraudio::MonoAmbisonicCodec<>> ambisonic_encoder;
public:
    MIN_DESCRIPTION    { "Encode point sources with desginated directions to ambisonic sound field." };
    MIN_TAGS        { "audio, sampling" };
    MIN_AUTHOR        { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };


    // constructor that allows for number of outlets to be defined by the ambisonic order argument.
    encoder(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),
        kNumOutputChannels(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),
        kNumSources(args.size()<2 ? 1 : int(args[1])), // if there is no second argument, set kNumSources = 1
        myAngle(vraudio::SphericalAngle::FromDegrees(0,0)),
        ambisonic_encoder(new vraudio::MonoAmbisonicCodec<>(kAmbisonicOrder, {myAngle}))
    { //body of constructor
        if(!args.empty() && (int(args[0]) > 3 || int(args[0]) < 1)){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        
        auto outlet_count = kNumOutputChannels;

        for (auto i=0; i < outlet_count; ++i) {
            //TODO the channel number should be in the assist message. String nonsense.
            auto an_outlet = std::make_unique<outlet<>>(this, "(signal) Channel", "signal");
            m_outlets.push_back( std::move(an_outlet) ); //TODO put this in one line
        }
    }
    
    message<> axisAngleList { this, "list", "message for angles",
        MIN_FUNCTION {
            if (inlet == 1)
                myAngle.set_azimuth(args[0]);
                myAngle.set_elevation(args[1]);
                ambisonic_encoder->set_angles({myAngle});
            return {};
        }
    };

    void operator()(audio_bundle input, audio_bundle output) {
        double* s = input.samples(0);
        audio_bundle tempIn(&s, 1, input.frame_count()); //this is very nasty and inelegant.
 
        auto nFrames = tempIn.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(1, nFrames);             // resonance-style mono audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumOutputChannels, nFrames);     // resonance-style audio buffer for output
        Min2Res(tempIn, &r_inputAudioBuffer);                             // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
        ambisonic_encoder->EncodeBuffer(r_inputAudioBuffer, &r_outputAudioBuffer);
        ///for now just copy the input buffer to the output buffer. Eventually this will become ambisonic processing
//        r_outputAudioBuffer = r_inputAudioBuffer; //utilize copy assignment defined by AudioBuffer class
        
        Res2Min(r_outputAudioBuffer, &output);                    // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(encoder);
