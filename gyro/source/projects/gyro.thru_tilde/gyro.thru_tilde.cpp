/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

//in this file, audio comes in, is converted twice, and goes out exactly the same as it came in

#include "c74_min.h"
#include "base/audio_buffer.h"
#include "audio_buffer_conversion.h"

using namespace c74::min;


class thru : public object<thru>, public vector_operator<> {
public:
    MIN_DESCRIPTION	{ "Pass input audio through, unchanged." };
    MIN_TAGS		{ "audio, sampling" };
    MIN_AUTHOR		{ "Cycling '74" };
    MIN_RELATED		{ "index~, buffer~, wave~" };

    inlet<>  in1	{ this, "(signal) Channel 1", "signal" };
    inlet<>  in2    { this, "(signal) Channel 2", "signal" };
    outlet<> out1		{ this, "(signal) Channel 1", "signal" };
    outlet<> out2        { this, "(signal) Channel 2", "signal" };

    void operator()(audio_bundle input, audio_bundle output) {
 
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(2, nFrames);      // resonance-style stereo audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(2, nFrames);     // resonance-style stereo audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);                      // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
        ///for now just copy the input buffer to the output buffer. Eventually this will become ambisonic processing
        r_outputAudioBuffer = r_inputAudioBuffer; //utilize copy assignment defined by AudioBuffer class
        
        Res2Min(r_outputAudioBuffer, &output);                    // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(thru);
