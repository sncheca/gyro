/// @file
///	@ingroup 	minexamples
///	@copyright	Copyright 2018 The Min-DevKit Authors. All rights reserved.
///	@license	Use of this source code is governed by the MIT License found in the License.md file.

//in this file, audio comes in, is converted twice, and goes out exactly the same as it came in

#include "c74_min.h"
#include "../../resonance_audio/base/audio_buffer.h"

using namespace c74::min;


class thru_index : public object<thru_index>, public vector_operator<> {
public:
    MIN_DESCRIPTION	{ "Read from a buffer~." };
    MIN_TAGS		{ "audio, sampling" };
    MIN_AUTHOR		{ "Cycling '74" };
    MIN_RELATED		{ "index~, buffer~, wave~" };

    inlet<>  index_inlet	{ this, "(signal) Sample index" };
    inlet<>  channel_inlet	{ this, "(float) Audio channel to use from buffer~" };
    outlet<> output			{ this, "(signal) Sample value at index", "signal" };
    outlet<> changed		{ this, "(symbol) Notification that the content of the buffer~ changed." };

    buffer_reference buffer { this,
        MIN_FUNCTION {    // will receive a symbol arg indicating 'binding', 'unbinding', or 'modified'
            changed.send(args);
            return {};
        }
    };

    argument<symbol> name_arg {this, "buffer-name", "Initial buffer~ from which to read.",
        MIN_ARGUMENT_FUNCTION {
            buffer.set(arg);
        }
    };

    argument<int> channel_arg {this, "channel", "Initial channel to read from the buffer~.",
        MIN_ARGUMENT_FUNCTION {
            channel = arg;
        }
    };

    attribute<int, threadsafe::no, limit::clamp> channel {this, "channel", 1,
        description {"Channel to read from the buffer~. The channel number uses 1-based counting."},
        range {1, buffer_reference::k_max_channels}
    };

    void operator()(audio_bundle input, audio_bundle output) {
        auto          in  = input.samples(0);                                     // get vector for channel 0 (first channel)
        auto          out = output.samples(0);                                    // get vector for channel 0 (first channel)
        buffer_lock<> b(buffer);                                                  // gain access to the buffer~ content
        auto          chan = std::min<size_t>(channel - 1, b.channel_count());    // convert from 1-based indexing to 0-based
        if (b.valid()) {
            vraudio::AudioBuffer r_inputAudioBuffer(1, input.frame_count());      // resonance-style mono audio buffer for input
            vraudio::AudioBuffer r_outputAudioBuffer(1, output.frame_count());    // resonance-style mono audio buffer for output
            
            //convert from audio_bundle to AudioBuffer. Eventually this will become the pita Min2Res() function; buf = Min2Res(bundle)
            for(auto c = 0; c < r_inputAudioBuffer.num_channels(); ++c){
                vraudio::AudioBuffer::Channel& r_channel = r_inputAudioBuffer[c];   //avoid double array subscript lookups-- slow
                //watch out for 0/1 indexing on channels!
                double* m_channel = input.samples(c);
                //copy the samples. Since samples() is a double array and channel view expects a float vector, need to copy by hand
                //need some checking for running of the end / make sure blocks have the same length. In theory, all channels have same num frames are their host buffer... but can never be too careful.
                for (size_t i = 0; i < r_inputAudioBuffer.num_frames(); ++i) {
                    r_channel[i] = m_channel[i];
                }
            }
            
            ///for now just copy the input buffer to the output buffer. Eventually this will become ambisonic processing
            r_outputAudioBuffer = r_inputAudioBuffer; //utilize copy assignment defined by AudioBuffer class
            
            ///convert from AudioBuffer to audio_bundle. Eventually this will become the pita Res2Min() function
            for(auto c = 0; c < output.channel_count(); ++c){
                double* m_channel = output.samples(c);
                vraudio::AudioBuffer::Channel& r_channel = r_outputAudioBuffer[c];
                for(auto i = 0; i < input.frame_count(); ++i){
                    m_channel[i] = r_channel[i];
                }
                //again watch out for indexing issues
//                output.samples(c) = r_outputAudioBuffer[c];
            }
            
            //original out
            for (auto i = 0; i < input.frame_count(); ++i) {
                auto frame = size_t(in[i] + 0.5);
                out[i]     = b.lookup(frame, chan);
            }
        }
        else {
            output.clear();
        }
    }
};


MIN_EXTERNAL(thru_index);
