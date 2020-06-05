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

typedef vector<double> interleavedSpkrLoc;

//TODO: this will have to copy...  I don't like that.
//determine the default locations for the speakers. Currently they are arranged in a 2D ring by default. TODO: update so that the default is 3D
std::vector<vraudio::SphericalAngle> initSpeakerLocations(const int nChannels){
    std::vector<vraudio::SphericalAngle> angles;
    for(int i = 0; i < nChannels; i++){
        angles.push_back(vraudio::SphericalAngle::FromDegrees(360*i/nChannels, 0));
    }
    return angles;
}

class speakerDecoder : public object<speakerDecoder>, public vector_operator<> {
private:
    //everything will be initialised in the member initialisation lists in the constructor
    const int kAmbisonicOrder;
    const int kNumInlets;
    const int kNumOutlets;
    std::vector<vraudio::SphericalAngle> speakerAngles;
    std::vector<double> vec;
    vraudio::AmbisonicCodecImpl<> speaker_decoder;

    std::vector< std::unique_ptr<inlet<>> >    m_inlets; //note that this must be called m_inputs!
    std::vector< std::unique_ptr<outlet<>> >    m_outlets; //note that this must be called m_outputs!
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
        speakerAngles(initSpeakerLocations(kNumOutlets)),
        vec(2*kNumOutlets, 0.0), //TODO: must be able to cast between sphericalAngle vector and interleaved vector.
        speaker_decoder(kAmbisonicOrder, speakerAngles)

    {
        
        //inlet handling
        //most max objects do not complain about extra arguments, so I don't either.
        if(!args.empty() && (int(args[0]) > 3 || int(args[0]) < 1)){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        
        std::string inletHelpMessage("(signal) Channel ");
        for (auto i=0; i < kNumInlets; ++i) {
            m_inlets.push_back( std::make_unique<inlet<>>(this, inletHelpMessage + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
        }
        
        std::string outletHelpMessage;
        for (auto i=0; i < kNumOutlets; ++i) {
            //hover over the outlet to learn its speaker location
            outletHelpMessage = "(signal) Channel " + std::to_string(i+1) + " (" + std::to_string(speakerAngles.at(i).azimuth()*vraudio::kDegreesFromRadians) + ", " + std::to_string(speakerAngles.at(i).elevation()*vraudio::kDegreesFromRadians) + ")";
            m_outlets.push_back( std::make_unique<outlet<>>(this, outletHelpMessage, "signal") );
        }
        
    }
    
    //a long vector that holds interleaved azimuth elevation values
    //TODO: initialise to variable size vector
    //note that vector<float> is not supported
    attribute< interleavedSpkrLoc > angles_attr { this, "spkr angles", vec,
        title{"Speaker Angles: interleaved (azimuth, elevation)"},
        description{"Speaker Angles: interleaved (azimuth, elevation)"},
        setter{MIN_FUNCTION{
            //TODO: scalable length
//            TODO: error check to make sure that the vector is the correct length
//            adjust the speakerAngles member. Potentially turn this into a constructor or cast
            for(int i = 0; i<kNumOutlets; i++){
                speakerAngles.at(i) = vraudio::SphericalAngle::FromDegrees(float(args[2*i]), float(args[2*i+1]));
                //TODO: update the outlet description, or get rid of angle in description
            }
            speaker_decoder.set_angles(speakerAngles); //update the speaker angles in the decoder
            return{};
        }},
        getter{ MIN_GETTER_FUNCTION{
            return{speakerAngles.at(0).azimuth()*vraudio::kDegreesFromRadians, speakerAngles.at(0).elevation()*vraudio::kDegreesFromRadians,
                   speakerAngles.at(1).azimuth()*vraudio::kDegreesFromRadians, speakerAngles.at(1).elevation()*vraudio::kDegreesFromRadians,
                   speakerAngles.at(2).azimuth()*vraudio::kDegreesFromRadians, speakerAngles.at(2).elevation()*vraudio::kDegreesFromRadians,
                   speakerAngles.at(3).azimuth()*vraudio::kDegreesFromRadians, speakerAngles.at(3).elevation()*vraudio::kDegreesFromRadians,
                   speakerAngles.at(4).azimuth()*vraudio::kDegreesFromRadians, speakerAngles.at(4).elevation()*vraudio::kDegreesFromRadians,
                   speakerAngles.at(5).azimuth()*vraudio::kDegreesFromRadians, speakerAngles.at(5).elevation()*vraudio::kDegreesFromRadians,
            };
        }
            
        }
    };
    
    void operator()(audio_bundle input, audio_bundle output) {

        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumInlets, nFrames);   // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumOutlets, nFrames);   // resonance-style audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);    // transfer audio data from min-style audio_bundle to resonance-style audioBuffer

        speaker_decoder.DecodeBuffer(r_inputAudioBuffer, &r_outputAudioBuffer);     //decode the buffer!
        //TODO: change to output below after adding the actual processing.
        Res2Min(r_outputAudioBuffer, &output);   // transfer audio data from resonance-style audioBuffer to min-style audio_bundle

    }
};


MIN_EXTERNAL(speakerDecoder);
