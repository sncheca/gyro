/*
Copyright 2020 Sofia Checa, Yale CCAM // Yale Blended Reality // Yale Department of Music

audio buffer conversion functions. Following the paradigm of Min, functions are collapsed into .h files instead of cpp files.
 
The Min API and the Resonance SDK have different objects for audio buffers. The samples of an audio bundle are an  2D array of doubles, while the samples of an AudioBuffer are separated into channels that are expect a vector of floats in their constructor.
 
The easiest way to interface between the two existing ecosystems is to simply convert between types whenever needed. This method is inefficient in that every audio buffer is copied twice per use, but other constructor-based conversion methods also do copies, using memcpy instead of iterative methods.

*/

#ifndef PITA_AUDIO_BUFFER_CONVERSION_H_
#define PITA_AUDIO_BUFFER_CONVERSION_H_

#include "c74_min.h" //for access to audio_bundle object
#include "base/audio_buffer.h" //for access to audioBuffer object and logging (for checks)

using namespace c74::min;

//convert audio_bundle object (Min) to AudioBuffer object (Resonance)
void Min2Res(audio_bundle& bundleIn, vraudio::AudioBuffer* bufferOut){
    DCHECK(bufferOut);
    //require that specs of the audio objects match
    DCHECK_EQ(bundleIn.channel_count(), bufferOut->num_channels());
    DCHECK_EQ(bundleIn.frame_count(), bufferOut->num_frames());
    auto nChannels = bundleIn.channel_count();
    auto nFrames = bundleIn.frame_count();
    
    //iterate through all channels
    for(auto c = 0; c < nChannels; ++c){
        vraudio::AudioBuffer::Channel& r_channel = (*bufferOut)[c];   //at the advice of resonance, avoid double array subscript lookups because they are slow (see base/audioBuffer.h)
        double* m_channel = bundleIn.samples(c);
        //need some checking for running of the end / make sure blocks have the same length. In theory, all channels have same num frames are their host buffer... but can never be too careful.
        //iterate through samples of each channel
        for (auto i = 0; i < nFrames; ++i) {
            r_channel[i] = m_channel[i];
        }
    }
    return;
}

//convert AudioBuffer object (Resonance) to audio_bundle object (Min)
void Res2Min(const vraudio::AudioBuffer& bufferIn, audio_bundle* bundleOut){
    //require that specs of the audio objects match
    DCHECK_EQ(bufferIn.num_channels(), bundleOut->channel_count());
    DCHECK_EQ(bufferIn.num_frames(), bundleOut->frame_count());
    auto nChannels = bufferIn.num_channels();
    auto nFrames = bufferIn.num_frames();
    
    //iterate through all channels
    for(auto c = 0; c < nChannels; ++c){
        double* m_channelOut = bundleOut->samples(c);
        const vraudio::AudioBuffer::Channel& r_channelOut = bufferIn[c];
        //iterate through samples of each channel
        for(auto i = 0; i < nFrames; ++i){
            m_channelOut[i] = r_channelOut[i];
        }
    }
    return;
}

#endif  // PITA_AUDIO_BUFFER_CONVERSION_H_




