/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

//in this file, audio comes in, is converted twice, and goes out exactly the same as it came in

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


class thru : public object<thru>, public vector_operator<> {
public:
    MIN_DESCRIPTION	{ "Encode a mono point source sound to ambisonic sound field. Make this more precise" };
    MIN_TAGS		{ "audio, sampling" };
    MIN_AUTHOR		{ "Cycling '74" };
    MIN_RELATED		{ "index~, buffer~, wave~" };

    inlet<>  in1	{ this, "(signal) Channel 1", "signal" };
    outlet<> out1		{ this, "(signal) Channel 1", "signal" };
    outlet<> out2        { this, "(signal) Channel 2", "signal" };
    outlet<> out3        { this, "(signal) Channel 3", "signal" };
    outlet<> out4        { this, "(signal) Channel 4", "signal" };

    void operator()(audio_bundle input, audio_bundle output) {
 
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(1, nFrames);      // resonance-style mono audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(4, nFrames);     // resonance-style audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);                      // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
        int AMBISONIC_ORDER = 1;
        //initialise the ambisonic codec object I'll be using
        vraudio::SphericalAngle myAngle = vraudio::SphericalAngle::FromDegrees(0,0);
        std::unique_ptr<vraudio::MonoAmbisonicCodec<>> aci(new vraudio::MonoAmbisonicCodec<>(AMBISONIC_ORDER, {myAngle}));
        
        aci->EncodeBuffer(r_inputAudioBuffer, &r_outputAudioBuffer);
        ///for now just copy the input buffer to the output buffer. Eventually this will become ambisonic processing
//        r_outputAudioBuffer = r_inputAudioBuffer; //utilize copy assignment defined by AudioBuffer class
        
        Res2Min(r_outputAudioBuffer, &output);                    // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(thru);
