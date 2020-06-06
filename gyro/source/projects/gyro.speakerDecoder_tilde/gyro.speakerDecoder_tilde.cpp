/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

///Copyright Sofia Checa 2020.

//decode a soundfield to a speaker array

#include "c74_min.h"
#include "ambisonics/ambisonic_codec.h"
#include "ambisonics/ambisonic_codec_impl.h"
#include "audio_buffer_conversion.h"

#include "ambisonics/associated_legendre_polynomials_generator.h"
#include "base/spherical_angle.h"

using namespace c74::min;
//note that the vraudio namespace is used for Resonance objects. I do not "use" this namespace so that is clear to the viewer where these objects come from

typedef vector<double> InterleavedList;

#define PITA_MIN_FUNCTION [this, i](const c74::min::atoms& args, int inlet) -> c74::min::atoms
#define PITA_MIN_GETTER_FUNCTION [this, i]() -> atoms

//TODO: this will have to copy...  I don't like that.
//determine the default angles for the speakers. Currently they are arranged in a 2D ring by default. TODO: update so that the default is 3D
std::vector<vraudio::SphericalAngle> initSpeakerAngles(const int nChannels){
    std::vector<vraudio::SphericalAngle> angles;
    for(int i = 0; i < nChannels; i++){
        angles.push_back(vraudio::SphericalAngle(vraudio::kTwoPi*i/nChannels, 0));
    }
    return angles;
}

//NOT ELEGANT, need to replace. Make these conversions more elegant. check using unique vectors. That might fix the copying issues.
//TODO: pre-allocate size, so save time with no pushback

//convert a vector of SphericalAngles to an interleaved buffer. InterleavedList type is always in degrees. TODO use operator overloading for this
InterleavedList sa2il(const std::vector<vraudio::SphericalAngle>& other){
    InterleavedList interleaved_buffer;
    for(int i = 0; i<other.size(); i++){
        interleaved_buffer.push_back(other.at(i).azimuth()*vraudio::kDegreesFromRadians);
        interleaved_buffer.push_back(other.at(i).elevation()*vraudio::kDegreesFromRadians);
    }
    return interleaved_buffer;
}


//cast an interleaved buffer to a vector of SphericalAngles. TODO: remove this
//std::vector<vraudio::SphericalAngle> il2sa(const InterleavedList other){
//    std::vector<vraudio::SphericalAngle> angles;
//    for(int i = 0; i < other.size(); i+=2){
//        angles.push_back(vraudio::SphericalAngle::FromDegrees(other[i], other[i+1]));
//    }
//    return angles;
//}

vector<atom> sa2atoms(const std::vector<vraudio::SphericalAngle>& other){
    vector<atom> a; //TODO: unique ptr for this? Could that fix the copying problem
    for(int i = 0; i<other.size(); i++){
        a.push_back(other.at(i).azimuth()*vraudio::kDegreesFromRadians);
        a.push_back(other.at(i).elevation()*vraudio::kDegreesFromRadians);
    }
    return a;
}

//convert an interleaved list to a vector of atoms.  TODO: remove this
//vector<atom> il2atoms(const InterleavedList other){
//    vector<atom> a;
//    for(int i = 0; i<other.size(); i++){
//        a.push_back(other[i]);
//    }
//    return a;
//}


class speakerDecoder : public object<speakerDecoder>, public vector_operator<> {
private:
    //everything will be initialised in the member initialisation lists in the constructor
    const int kAmbisonicOrder;
    const int kNumInlets;
    const int kNumOutlets;
    std::vector<vraudio::SphericalAngle> speakerAngles; //TODO: think about using set_azimuth and set_elevation instead of remaking the entire angle
    vraudio::AmbisonicCodecImpl<> speaker_decoder;

    std::vector< std::unique_ptr<inlet<>> >    m_inlets; //note that this must be called m_inputs!
    std::vector< std::unique_ptr<outlet<>> >    m_outlets; //note that this must be called m_outputs!
    std::vector< attribute<vector<double>>* > m_attr;
    
public:
    MIN_DESCRIPTION    { "Decodes a soundfield to binaural. Use argument to select ambisonic order. Ambisonic order 1 by default." };
    MIN_TAGS           { "gyro, binaural, ambisonics, audio" };
    MIN_AUTHOR         { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };
    
    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    speakerDecoder(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),    //set the default ambisonic order to 1 if there are no arguments
        kNumInlets(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),   //determine how many spherical harmonics there are for this order
        kNumOutlets(args.size()<2 ? kNumInlets : int(args[1])), // if there is no second argument, set kNumOutlets = kNumInlets. TODO: what does this mean for @channel 16
        speakerAngles(initSpeakerAngles(kNumOutlets)),
        speaker_decoder(kAmbisonicOrder, speakerAngles)

    {
        //just some testing of the conversion between interleaved list and angles vector
        print(speakerAngles);
        print(sa2il(speakerAngles));
//        print(il2sa(sa2il(speakerAngles)));
        
        //inlet handling
        //most max objects do not complain about extra arguments, so I don't either.
        if(!args.empty() && (int(args[0]) > 3 || int(args[0]) < 1)){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        
        std::string inletHelpMessage("(signal) Channel ");
        for (auto i=0; i < kNumInlets; ++i) {
            m_inlets.push_back( std::make_unique<inlet<>>(this, inletHelpMessage + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
        }
        
        std::string outletHelpMessage, attributeName;
        attribute< vector<double> >* speakerPosition_attr;
        for (auto i=0; i < kNumOutlets; ++i) {
            //create outlets
            outletHelpMessage = "(signal) Channel " + std::to_string(i+1);
//            outletHelpMessage = "(signal) Channel " + std::to_string(i+1) + " (" + std::to_string(speakerAngles.at(i).azimuth()*vraudio::kDegreesFromRadians) + ", " + std::to_string(speakerAngles.at(i).elevation()*vraudio::kDegreesFromRadians) + ")";
            m_outlets.push_back( std::make_unique<outlet<>>(this, outletHelpMessage, "signal") );
            
            //create an attribute for each output channel's angles
            //TODO: definitely some pointer work to be done here and throughout
            attributeName = "Spkr " + std::to_string(i+1) + " angles";
            speakerPosition_attr = new attribute< vector<double> >{ this, attributeName, {0.0, 0.0},
                description{"Set a speaker's direction using (azimuth, elevation) in degrees."},
                setter{ PITA_MIN_FUNCTION{
                    int speakerID = i;
                    speakerAngles.at(speakerID).set_azimuth(float(args[0])*vraudio::kRadiansFromDegrees);
                    speakerAngles.at(speakerID).set_elevation(float(args[1])*vraudio::kRadiansFromDegrees);
                    speaker_decoder.set_angles(speakerAngles); //update the angles in the decoder
                    return {};
                }},
                getter{ PITA_MIN_GETTER_FUNCTION{
                    int speakerID = i;
                    return {speakerAngles.at(speakerID).azimuth()*vraudio::kDegreesFromRadians,
                            speakerAngles.at(speakerID).elevation()*vraudio::kDegreesFromRadians
                    };
                }}
            }; //TODO: would be nice to have this as spherical angle type
            
            m_attr.push_back(speakerPosition_attr);
            
        }
                
    }
    
    //TODO: delete this
    void print(const InterleavedList& il){
        for(int i = 0; i<il.size(); i++){
            cout << il[i] << " ";
        }
        cout << endl;
    }
    
    //TODO: delete this
    void print(const std::vector<vraudio::SphericalAngle>& angles){
        for(int i = 0; i < angles.size(); i++){
            cout << angles.at(i).azimuth()*vraudio::kDegreesFromRadians << " " << angles.at(i).elevation()*vraudio::kDegreesFromRadians << " ";
        }
        cout << endl;
    }
    
    message<> setSpeakerAngles { this, "set", "Set a speaker's location using (azimuth, elevation) in degrees",
        MIN_FUNCTION {
            cout << "got a message" << endl;
            if(args.size() == 3){
                int speakerID = args[0];
                if(speakerID > 0 && speakerID <= kNumOutlets){ //if the user enters a speaker number that is out of range
                    speakerAngles.at(speakerID-1) = vraudio::SphericalAngle::FromDegrees(args[1], args[2]); //human is 1-indexed, internal is 0-indexed
//                    m_attr.at(speakerID) = {float(args[1]), float(args[2])}; //TODO: assign attribute from message
                    speaker_decoder.set_angles(speakerAngles);
                } else {
                cerr << "Invalid speakerID. Speaker decoder currently has " << kNumOutlets << "output channels" << endl;
                }
            } else {
                //some error message telling them how to use it
                cerr << "Message usage: send a message with a list in the form [set <speakerID> <azimuth> <elevation>]" << endl;
            }
            return {};
        }
    };
    
    //a long vector that holds interleaved azimuth elevation values
    //note that vector<float> is not supported
    //TODO: attr style
    attribute< InterleavedList > angles_attr { this, "spkr angles", sa2il(speakerAngles),
        title{"Speaker Angles: interleaved (azimuth, elevation)"},
        description{"Speaker Angles: interleaved (azimuth, elevation)"},
        setter{MIN_FUNCTION{
//            TODO: error check to make sure that the vector is the correct length
//            adjust the speakerAngles member. Potentially turn this into a constructor or cast. Careful cause we're not making a new one, we're updating the one we have
            for(int i = 0; i<kNumOutlets; i++){
                speakerAngles.at(i) = vraudio::SphericalAngle::FromDegrees(float(args[2*i]), float(args[2*i+1]));
            }
            speaker_decoder.set_angles(speakerAngles); //update the speaker angles in the decoder
            return{};
        }},
        getter{ MIN_GETTER_FUNCTION{
            return sa2atoms(speakerAngles);
        }
            
        }
    };
    
    void operator()(audio_bundle input, audio_bundle output) {

        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumInlets, nFrames);   // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumOutlets, nFrames);   // resonance-style audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);    // transfer audio data from min-style audio_bundle to resonance-style audioBuffer

        speaker_decoder.DecodeBuffer(r_inputAudioBuffer, &r_outputAudioBuffer);     //decode the buffer!
        Res2Min(r_outputAudioBuffer, &output);   // transfer audio data from resonance-style audioBuffer to min-style audio_bundle

    }
};


MIN_EXTERNAL(speakerDecoder);
