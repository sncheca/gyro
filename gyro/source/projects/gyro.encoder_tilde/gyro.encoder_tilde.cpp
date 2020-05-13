/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

//an ambisonic encoder that supports 1st, 2nd, and 3rd order ambisonics. 

#include "c74_min.h"
#include "../../resonance_audio/ambisonics/ambisonic_codec_impl.h"
#include "../../resonance_audio/ambisonics/ambisonic_codec.h"
#include "../../pita/audio_buffer_conversion.h"

//things that are included in the above res files
//#include <cmath>
//#include <vector>
//#include "../Eigen/Dense" //not needed
//#include "ambisonics/ambisonic_codec.h" //no .cpp file
#include "../../resonance_audio/ambisonics/associated_legendre_polynomials_generator.h" //yes needed
//#include "../../resonance_audio/ambisonics/utils.h" //no .cpp file
//#include "base/audio_buffer.h" //already in pita
//#include "base/constants_and_types.h" //in audio_buffer
//#include "base/logging.h" //in audio_buffer
#include "../../resonance_audio/base/spherical_angle.h" //yes needed
//#include "utils/pseudoinverse.h" //no .cpp file

using namespace c74::min;

class encoder : public object<encoder>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumOuts;
    std::vector< std::unique_ptr<outlet<>> >    m_inlets; //note that this must be called m_outputs!
public:
    MIN_DESCRIPTION    { "Encode a mono point source sound to ambisonic sound field. Make this more precise" };
    MIN_TAGS        { "audio, sampling" };
    MIN_AUTHOR        { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };

    inlet<>  in1    { this, "(signal) Channel 1", "signal" };
//    outlet<> out1		{ this, "(signal) Channel 1", "signal" };
//    outlet<> out2        { this, "(signal) Channel 2", "signal" };
//    outlet<> out3        { this, "(signal) Channel 3", "signal" };
//    outlet<> out4        { this, "(signal) Channel 4", "signal" };
    
    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    encoder(const atoms& args = {}):kAmbisonicOrder(args[0]), kNumOuts((kAmbisonicOrder+1)*(kAmbisonicOrder+1)) { //TODO turn this into a function. see hoa_rotator.cc for GetNumNthOrder
        if (args.empty()){
            error("Argument required. Please include the ambisonic order.");
        } else if(int(args[0]) > 3 || int(args[0]) < 1){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        auto outlet_count = kNumOuts;

        for (auto i=0; i < outlet_count; ++i) {
            //TODO the channel number should be in the assist message. String nonsense.
            auto an_outlet = std::make_unique<outlet<>>(this, "(signal) Channel", "signal");
            m_inlets.push_back( std::move(an_outlet) );
        }
    }

    void operator()(audio_bundle input, audio_bundle output) {
 
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(1, nFrames);             // resonance-style mono audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumOuts, nFrames);     // resonance-style audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);                             // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
        //initialise the ambisonic codec object I'll be using
        vraudio::SphericalAngle myAngle = vraudio::SphericalAngle::FromDegrees(0,0);
        std::unique_ptr<vraudio::MonoAmbisonicCodec<>> aci(new vraudio::MonoAmbisonicCodec<>(kAmbisonicOrder, {myAngle}));
        
        aci->EncodeBuffer(r_inputAudioBuffer, &r_outputAudioBuffer);
        ///for now just copy the input buffer to the output buffer. Eventually this will become ambisonic processing
//        r_outputAudioBuffer = r_inputAudioBuffer; //utilize copy assignment defined by AudioBuffer class
        
        Res2Min(r_outputAudioBuffer, &output);                    // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(encoder);
