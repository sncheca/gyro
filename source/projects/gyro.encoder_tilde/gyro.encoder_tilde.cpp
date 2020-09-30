/// @file
///    @ingroup     gyro
///    @copyright    Copyright 2020 Sofia Checa
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

// Copyright 2020 Sofia Checa
// This work was funded by Yale Department of Music // Yale CCAM // Yale Blended Reality

//a multichannel ambisonic encoder that supports 1st, 2nd, and 3rd order ambisonics.

#include "c74_min.h"
#include "ambisonics/ambisonic_codec_impl.h"
#include "ambisonics/ambisonic_codec.h"
#include "audio_buffer_conversion.h"
#include "pita_spherical_angle.h"
#include "pita_port.h"

#include "ambisonics/associated_legendre_polynomials_generator.h"
#include "base/spherical_angle.h"

using namespace c74::min;

void setDefaultSourceAngles(std::vector<vraudio::SphericalAngle>& angles){
    int nSpeakers = angles.size();
    for(int i = 0; i < nSpeakers; i++){
        angles.at(i).set_azimuth(0);
        angles.at(i).set_elevation(0);
    }
    return;
}

class encoder : public object<encoder>, public vector_operator<> {
private:
    const int kAmbisonicOrder;
    const int kNumOutputChannels;
    const int kNumSources;
    std::vector<vraudio::SphericalAngle> source_angles;
//    std::unique_ptr<vraudio::MonoAmbisonicCodec<>> ambisonic_encoder;
    vraudio::AmbisonicCodecImpl<> ambisonic_encoder;
    
    std::vector< std::unique_ptr<pita::p_inlet> >    g_inlets;
    std::vector< std::unique_ptr<outlet<>> >    g_outlets;
    
public:
    MIN_DESCRIPTION    { "Encode point sources with desginated directions to ambisonic sound field." };
    MIN_TAGS        { "gyro, encoder, ambisonics, audio" };
    MIN_AUTHOR        { "Sofia Checa" };
    MIN_RELATED        { " gyro.binauralDecoder~, gyro.speakerDecoder~, gyro.rotator~, gyro.soundfield2Stereo~, gyro.thru~" };

    // constructor that allows for number of outlets to be defined by the ambisonic order argument.
    encoder(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),
        kNumOutputChannels(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),
        kNumSources(args.size()<2 ? 1 : int(args[1])), // if there is no second argument, set kNumSources = 1
        source_angles(std::vector<vraudio::SphericalAngle>(kNumSources, vraudio::SphericalAngle::FromDegrees(0,0))), //all sources will start at position (0,0). This will create a nice spreading effect when you move them -- good for demos :)
        ambisonic_encoder(kAmbisonicOrder, source_angles)
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
        
        for (auto i=0; i < kNumSources; ++i) {
            g_inlets.push_back( std::make_unique<pita::p_inlet>(this, pita::generatePortAngleLabel(i, source_angles), "signal") ); 
        }
        
        for (auto i=0; i < kNumOutputChannels; ++i) {
            g_outlets.push_back( std::make_unique<outlet<>>(this, "(signal) Soundfield Channel " + std::to_string(i+1), "signal") );
        }
        
        //one more outlet for dumping out speaker angle information
        g_outlets.push_back( std::make_unique<outlet<>>(this, "(list) Interleaved list of source angles (°) in axis-angle, i.e., [1 <azimuth1> <elevation1> 2 <azimuth2> <elevation2> ...]", "list") );
    }
    
    // Dump interleaved list of source angles (°) in axis-angle out of last outlet
    message<> getSourceAngles {this, "getAngles", "Dump interleaved list of source angles (°) in axis-angle out of last outlet",
        MIN_FUNCTION{
            g_outlets.back()->send(pita::sa2atoms(source_angles));
            return{};
        }
    };
    
    // Bang equivalent of the getSpeakerAngles (above). Dump interleaved list of source angles (°) in axis-angle out of last outlet
    message<> bangSpeakerAngles {this, "bang", "Dump interleaved list of source angles (°) in axis-angle out of last outlet",
        MIN_FUNCTION{
            g_outlets.back()->send(pita::sa2atoms(source_angles));
            return{};
        }
    };
    
    //TODO: can we consolidate anything from the equivalent in the decoder?
    message<> setSourceAngles { this, "set", "Set a source's location using (azimuth, elevation) in degrees",
        MIN_FUNCTION {
            int argc = args.size(); //C-style, avoid repetition.
            if(argc % 3 == 0){
                //disregard the entire message if it is poorly formatted. There are too many ways to make a mistake, it's not worth trying to extract some meaning from it.
                for(int i = 0; i < argc; i+=3){
                    int sourceID = int(args[i])-1; //internal speakerID is 0 indexed.
                    if(sourceID >= 0 && sourceID < kNumSources){ //if the user enters a speaker number that is out of range
                        vraudio::SphericalAngle unsimplifiedSphericalAngle = vraudio::SphericalAngle::FromDegrees(float(args[i+1]), float(args[i+2]));
                        source_angles.at(sourceID) = vraudio::SphericalAngle::FromWorldPosition(unsimplifiedSphericalAngle.GetWorldPositionOnUnitSphere());
                        g_inlets.at(sourceID)->setDescription(pita::generatePortAngleLabel(sourceID, source_angles));
                    } else {
                    cerr << "Input channel " << sourceID+1 << " is out of range. Ambisonic encoder currently has " << kNumSources << " input channels." << endl;
                    }
                }
                //after updating all the individual speaker angles, update the decoder's angles and dump out the angles.
                ambisonic_encoder.set_angles(source_angles);
                g_outlets.back()->send(pita::sa2atoms(source_angles));
            
            } else {
                // error message telling them how to use it
                cerr << "Angles have not been set due to a poorly formatted message. Message usage: interleaved list in the form [set <speaker1ID> <azimuth1> <elevation1> <speaker2ID> <azimuth2> <elevation2>]" << endl;
            }
            return {};
        }
    };
                        
    // reset source angles to (0,0)
    message<> resetSpeakerAngles{this, "reset", "Reset speaker angles to default.",
        MIN_FUNCTION{
            setDefaultSourceAngles(source_angles);
            ambisonic_encoder.set_angles(source_angles);
            //reset all the labels too
            for(int i = 0; i < kNumSources; i++){
                g_inlets.at(i)->setDescription(pita::generatePortAngleLabel(i, source_angles));
            }
            g_outlets.back()->send(pita::sa2atoms(source_angles));
            return{};
        }
    };

    void operator()(audio_bundle input, audio_bundle output) {
 
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumSources, nFrames);  // resonance-style mono audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumOutputChannels, nFrames);     // resonance-style audio buffer for output
        pita::Min2Res(input, &r_inputAudioBuffer); // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
        ambisonic_encoder.EncodeBuffer(r_inputAudioBuffer, &r_outputAudioBuffer); //encode the buffer!
        
        pita::Res2Min(r_outputAudioBuffer, &output);  // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
       
    }
};


MIN_EXTERNAL(encoder);
