/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

//an ambisonic encoder that supports 1st, 2nd, and 3rd order ambisonics. 

#include "c74_min.h"
#include "ambisonics/ambisonic_codec_impl.h"
#include "ambisonics/ambisonic_codec.h"
#include "audio_buffer_conversion.h"
#include "pita_spherical_angle.h"

#include "ambisonics/associated_legendre_polynomials_generator.h"
#include "base/spherical_angle.h" //yes needed

using namespace c74::min;

class encoder : public object<encoder>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumOutputChannels;
    const int kNumSources;
    std::vector<vraudio::SphericalAngle> source_angles;
    std::unique_ptr<vraudio::MonoAmbisonicCodec<>> ambisonic_encoder;
    
    std::vector< std::unique_ptr<inlet<>> >    g_inlets;
    std::vector< std::unique_ptr<outlet<>> >    g_outlets;
    
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
        source_angles(std::vector<vraudio::SphericalAngle>(1, vraudio::SphericalAngle::FromDegrees(0,0))), //all sources will start at position (0,0). This will create a nice spreading effect when you move them -- good for demos :)
        ambisonic_encoder(new vraudio::MonoAmbisonicCodec<>(kAmbisonicOrder, source_angles))
    { //body of constructor
        if(!args.empty() && (int(args[0]) > 3 || int(args[0]) < 1)){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        
        for (auto i=0; i < kNumSources; ++i) {
            g_inlets.push_back( std::make_unique<inlet<>>(this, "(signal) Source " + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
        }
        
        for (auto i=0; i < kNumOutputChannels; ++i) {
            g_outlets.push_back( std::make_unique<outlet<>>(this, "(signal) Channel " + std::to_string(i+1), "signal") );
        }
        
        //one more outlet for dumping out speaker angle information
        g_outlets.push_back( std::make_unique<outlet<>>(this, "(list) Interleaved list of source angles (°) in axis-angle, i.e., [1 <azimuth1> <elevation1> 2 <azimuth2> <elevation2> ...]", "list") );
    }
    
    //TODO: can we consolidate anything from the equivalent in the decoder?
    message<> setSourceAngles { this, "set", "Set a source's location using (azimuth, elevation) in degrees",
        MIN_FUNCTION {
            int argc = args.size(); //C-style, avoid repetition.
            if(argc % 3 == 0){ //disregard the entire message if it is poorly formatted. There are too many ways to make a mistake, it's not worth trying to extract some meaning from it.
                for(int i = 0; i < argc; i+=3){
                    int sourceID = int(args[i])-1; //internal speakerID is 0 indexed.
                    if(sourceID >= 0 && sourceID < kNumSources){ //if the user enters a speaker number that is out of range
                        source_angles.at(sourceID).set_azimuth(float(args[i+1])*vraudio::kRadiansFromDegrees);
                        source_angles.at(sourceID).set_elevation(float(args[i+2])*vraudio::kRadiansFromDegrees);
//                        g_inlets.at(sourceID)->setDescription("(signal) Channel " + std::to_string(sourceID+1) + " (" + std::to_string(int(args[i+1])) + "°, " + std::to_string(int(args[i+2])) + "°)");
                    } else {
                    cerr << "Input channel " << sourceID+1 << " is out of range. Ambisonic encoder currently has " << kNumSources << "input channels." << endl;
                    }
                }
                //after updating all the individual speaker angles, update the decoder's angles and dump out the angles.
                ambisonic_encoder->set_angles(source_angles);
                g_outlets.back()->send(pita::sa2atoms(source_angles));
            
            } else {
                // error message telling them how to use it
                cerr << "Angles have not been set due to a poorly formatted message. Message usage: interleaved list in the form [set <speaker1ID> <azimuth1> <elevation1> <speaker2ID> <azimuth2> <elevation2>]" << endl;
            }
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
