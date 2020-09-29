/// @file
///    @ingroup     gyro
///    @copyright    Copyright 2020 Sofia Checa
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

// Copyright 2020 Sofia Checa
// This work was funded by Yale Department of Music // Yale CCAM // Yale Blended Reality

//decode a soundfield to a speaker array

#include "c74_min.h"
#include "ambisonics/ambisonic_codec.h"
#include "ambisonics/ambisonic_codec_impl.h"
#include "audio_buffer_conversion.h"
#include "pita_spherical_angle.h"
#include "pita_port.h" //for p_outlet, a derived class that allows the m_description to be modified.

#include "ambisonics/associated_legendre_polynomials_generator.h"
#include "base/spherical_angle.h"

using namespace c74::min;
//note that the vraudio namespace is used for Resonance objects. I do not "use" this namespace so that is clear to the viewer where these objects come from

// gets called by both initSpeakerAngles and reset message
void setDefaultSpeakerAngles(std::vector<vraudio::SphericalAngle>& angles){
    int nSpeakers = angles.size();
    for(int i = 0; i < nSpeakers; i++){
        angles.at(i).set_azimuth(vraudio::kTwoPi*i/nSpeakers);
        angles.at(i).set_elevation(0);
    }
    return;
}

//determine the default angles for the speakers. Currently they are arranged in a 2D ring by default. TODO: update so that the default is 3D
std::vector<vraudio::SphericalAngle> initSpeakerAngles(const int nChannels){
    std::vector<vraudio::SphericalAngle> angles(nChannels, vraudio::SphericalAngle()); //preallocate is better practice
    setDefaultSpeakerAngles(angles);
    return angles;
}

class speakerDecoder : public object<speakerDecoder>, public vector_operator<> {
private:
    //initialised in the member initialisation lists
    const int kAmbisonicOrder;
    const int kNumInlets;
    const int kNumSpeakers;
    std::vector<vraudio::SphericalAngle> speaker_angles; //stored in radians, exposed in degrees
    vraudio::AmbisonicCodecImpl<> speaker_decoder;

    std::vector< std::unique_ptr<inlet<>> >    g_inlets;
    std::vector< std::unique_ptr<pita::p_outlet> >    g_outlets;
    
public:
    MIN_DESCRIPTION    { "Decode a soundfield to a speaker array. Use argument to select ambisonic order. Ambisonic order 1 by default." };
    MIN_TAGS           { "gyro, decoder, ambisonics, audio" };
    MIN_AUTHOR         { "Sofia Checa" };
    MIN_RELATED        { "gyro.encoder~, gyro.binauralDecoder~, gyro.rotator~, gyro.soundfield2Stereo~, gyro.thru~" };
    
    // constructor that allows for number of outlets to be defined by the ambisonic order argument.
    speakerDecoder(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),    //set the default ambisonic order to 1 if there are no arguments
        kNumInlets(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),   //determine how many spherical harmonics there are for this order
        kNumSpeakers(args.size()<2 ? kNumInlets : int(args[1])), // if there is no second argument, set kNumOutlets = kNumInlets
        speaker_angles(initSpeakerAngles(kNumSpeakers)),
        speaker_decoder(kAmbisonicOrder, speaker_angles)

    {   //body of the constructor
        
        //most max objects do not complain about extra arguments, so I don't either.
        if(!args.empty() && (int(args[0]) > 5 || int(args[0]) < 1)){
            error("This package currently only supports ambisonic orders 1 through 5.");
        }
        
        /*
         the number of speakers must be greater than or equal to the number of harmonics. If the number of speakers is less, then the soundfield is folded down, resulting in pockets of space that get very loud. I wouldn't consider this behaviour to be undefined, but it is certainly unpredictable. I can imagine that an inexperienced user could be in for an unpleasant (and costly) surprise. For that reason, I limit the speakerDecoder object so that it can only be created with this requirement satisfied. If a user wants to use fewer speakers with a higher order, then she just won't connect all the outlets.
         */
        if(kNumSpeakers < kNumInlets){
            error("The number of speakers must be greater than or equal to " + std::to_string(kNumInlets) + " (number of spherical harmonics).");
        }
        
        // create inlets
        for (auto i=0; i < kNumInlets; ++i) {
            g_inlets.push_back( std::make_unique<inlet<>>(this, "(signal) Soundfield Channel " + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
        }
        
        // create outlets
        for (auto i=0; i < kNumSpeakers; ++i) {
            g_outlets.push_back( std::make_unique<pita::p_outlet>(this, pita::generatePortAngleLabel(i, speaker_angles), "signal") );
            
        }
        
        //one more outlet for dumping out speaker angle information
        g_outlets.push_back( std::make_unique<pita::p_outlet>(this, "(list) Interleaved list of speaker angles (°) in axis-angle, i.e., [1 <azimuth1> <elevation1> 2 <azimuth2> <elevation2> ...]", "list") );
    }
    
    // Dump interleaved list of speaker angles (°) in axis-angle out of last outlet
    message<> getSpeakerAngles {this, "getAngles", "Dump interleaved list of speaker angles (°) in axis-angle out of last outlet",
        MIN_FUNCTION{
            g_outlets.back()->send(pita::sa2atoms(speaker_angles));
            return{};
        }
    };
    
    // Bang equivalent of the getSpeakerAngles (above). Dump interleaved list of speaker angles (°) in axis-angle out of last outlet
    message<> bangSpeakerAngles {this, "bang", "Dump interleaved list of speaker angles (°) in axis-angle out of last outlet",
        MIN_FUNCTION{
            g_outlets.back()->send(pita::sa2atoms(speaker_angles));
            return{};
        }
    };
    
    message<> setSpeakerAngles { this, "set", "Set a speaker's location using (azimuth, elevation) in degrees",
        MIN_FUNCTION {
            int argc = args.size(); //C-style, avoid repetition.
            if(argc % 3 == 0){ //disregard the entire message if it is poorly formatted. There are too many ways to make a mistake, it's not worth trying to extract some meaning from it.
                for(int i = 0; i < argc; i+=3){
                    int speakerID = int(args[i])-1; //internal speakerID is 0 indexed.
                    if(speakerID >= 0 && speakerID < kNumSpeakers){ //if the user enters a speaker number that is out of range
                        vraudio::SphericalAngle unsimplifiedSphericalAngle = vraudio::SphericalAngle::FromDegrees(float(args[i+1]), float(args[i+2]));
                        speaker_angles.at(speakerID) = vraudio::SphericalAngle::FromWorldPosition(unsimplifiedSphericalAngle.GetWorldPositionOnUnitSphere());
                        g_outlets.at(speakerID)->setDescription(pita::generatePortAngleLabel(speakerID, speaker_angles));
                    } else {
                    cerr << "Output channel " << speakerID+1 << " is out of range. Speaker decoder currently has " << kNumSpeakers << " output channels." << endl;
                    }
                }
                //after updating all the individual speaker angles, update the decoder's angles and dump out the angles.
                speaker_decoder.set_angles(speaker_angles);
                g_outlets.back()->send(pita::sa2atoms(speaker_angles));
            
            } else {
                // error message telling them how to use it
                cerr << "Angles have not been set due to a poorly formatted message. Message usage: interleaved list in the form [set <speaker1ID> <azimuth1> <elevation1> <speaker2ID> <azimuth2> <elevation2>]" << endl;
            }
            return {};
        }
    };
    
    // reset speaker angles to their default values 
    message<> resetSpeakerAngles{this, "reset", "Reset speaker angles to default.",
        MIN_FUNCTION{
            setDefaultSpeakerAngles(speaker_angles);
            speaker_decoder.set_angles(speaker_angles);
            for(int i = 0; i < kNumSpeakers; i++){
                g_outlets.at(i)->setDescription(pita::generatePortAngleLabel(i, speaker_angles));
            }
            g_outlets.back()->send(pita::sa2atoms(speaker_angles));
            return{};
        }
    };
            
    void operator()(audio_bundle input, audio_bundle output) {

        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumInlets, nFrames);   // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumSpeakers, nFrames);   // resonance-style audio buffer for output
        pita::Min2Res(input, &r_inputAudioBuffer);    // transfer audio data from min-style audio_bundle to resonance-style audioBuffer

        speaker_decoder.DecodeBuffer(r_inputAudioBuffer, &r_outputAudioBuffer);     //decode the buffer!
        pita::Res2Min(r_outputAudioBuffer, &output);   // transfer audio data from resonance-style audioBuffer to min-style audio_bundle

    }
};

MIN_EXTERNAL(speakerDecoder);
