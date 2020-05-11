/*
Copyright 2020 Sofia Checa, Yale CCAM // Yale Blended Reality // Yale Department of Music

audio buffer conversion functions. Following the paradigm of Min, functions are collapsed into .h files instead of cpp files.
 
The Min API and the Resonance SDK have different objects for audio buffers. The samples of an audio bundle are an  2D array of doubles, while the samples of an AudioBuffer are separated into channels that are expect a vector of floats in their constructor.
 
The easiest way to interface between the two existing ecosystems is to simply convert between types whenever needed. This method is inefficient in that every audio buffer is copied twice per use, but other constructor-based conversion methods also do copies, using memcpy instead of iterative methods.

*/

#ifndef PITA_AUDIO_BUFFER_CONVERSION_H_
#define PITA_AUDIO_BUFFER_CONVERSION_H_

#include "c74_min.h" //for access to audio_bundle object
#include "../resonance_audio/base/audio_buffer.h" //for access to audioBuffer object and logging (for checks)

using namespace c74::min;

//convert audio_bundle object (Min) to AudioBuffer object (Resonance)
void Min2Res(audio_bundle& bundle, vraudio::AudioBuffer* buffer){
    //require that specs of the audio objects match
    DCHECK_EQ(bundle.channel_count(), buffer->num_channels());
    DCHECK_EQ(bundle.frame_count(), buffer->num_frames());
    auto nChannels = bundle.channel_count();
    auto nFrames = bundle.frame_count();
    
    //iterate through all channels
    for(auto c = 0; c < nChannels; ++c){
        vraudio::AudioBuffer::Channel& r_channel = (*buffer)[c];   //at the advice of resonance, avoid double array subscript lookups because they are slow (see base/audioBuffer.h)
        double* m_channel = bundle.samples(c);
        //need some checking for running of the end / make sure blocks have the same length. In theory, all channels have same num frames are their host buffer... but can never be too careful.
        //iterate through samples of each channel
        for (auto i = 0; i < nFrames; ++i) {
            r_channel[i] = m_channel[i];
        }
    }
    return;
}

//convert AudioBuffer object (Resonance) to audio_bundle object (Min)
void Res2Min(const vraudio::AudioBuffer& buffer, audio_bundle* bundle){
    //require that specs of the audio objects match
    DCHECK_EQ(buffer.num_channels(), bundle->channel_count());
    DCHECK_EQ(buffer.num_frames(), bundle->frame_count());
    auto nChannels = buffer.num_channels();
    auto nFrames = buffer.num_frames();
    
    //iterate through all channels
    for(auto c = 0; c < nChannels; ++c){
        double* m_channelOut = bundle->samples(c);
        const vraudio::AudioBuffer::Channel& r_channelOut = buffer[c];
        //iterate through samples of each channel
        for(auto i = 0; i < nFrames; ++i){
            m_channelOut[i] = r_channelOut[i];
        }
    }
    return;
}

#endif  // PITA_AUDIO_BUFFER_CONVERSION_H_




