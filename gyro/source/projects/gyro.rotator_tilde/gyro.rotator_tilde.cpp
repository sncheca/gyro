/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

///Copyright Sofia Checa 2020.

//binaurally render a soundfield, using HRTFs

#include "c74_min.h"
#include "ambisonics/hoa_rotator.h"
#include "audio_buffer_conversion.h"
#include "ambisonics/utils.h"

#include "third_party/eigen/Eigen/Dense" //to use quaternion constructor
#include "third_party/eigen/unsupported/Eigen/EulerAngles" //to use euler conversions. Note that the one provided in Dense does not have the Euler class.

using namespace c74::min;

class rotator : public object<rotator>, public vector_operator<> {
private:
    //everything will be initialised in the member initialisation lists in the constructor
    const int kAmbisonicOrder;
    const int kNumSphericalHarmonics;
    const int kNumInlets;
    const int kNumOutlets;
    Eigen::Quaternionf quaternion; //keep this as a member since it can be updated by either quaternion_attr or euler_attr
    Eigen::EulerAngles<float, Eigen::EulerAnglesXYZd> euler_angles;
    vraudio::WorldRotation world_rotation; //keep this as a member to avoid repeated calculations
    vraudio::HoaRotator hoa_rotator;

    std::vector< std::unique_ptr<inlet<>> >    m_inlets; //note that this must be called m_inputs!
    std::vector< std::unique_ptr<outlet<>> >   m_outlets; //must be called m_outputs

public:
    MIN_DESCRIPTION    { "Rotate a soundfield. Use argument to select ambisonic order. Ambisonic order 1 by default." };
    MIN_TAGS           { "gyro, encoder, binauralDecoder, ambisonics, audio" };
    MIN_AUTHOR         { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };
    
    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    rotator(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),    //set the default ambisonic order to 1 if there are no arguments
        kNumSphericalHarmonics(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),   //determine how many spherical harmonics there are for this order
        kNumInlets(kNumSphericalHarmonics),
        kNumOutlets(kNumSphericalHarmonics),
        hoa_rotator(kAmbisonicOrder)
        {
        
        //inlet handling. Most max objects do not complain about extra arguments, so I don't either.
        if(!args.empty() && (int(args[0]) > 3 || int(args[0]) < 1)){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        std::string inletHelpMessage("(signal) Channel ");
        for (auto i=0; i < kNumOutlets; ++i) {
            m_inlets.push_back( std::make_unique<inlet<>>(this, inletHelpMessage + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
            m_outlets.push_back( std::make_unique<outlet<>>(this, inletHelpMessage + std::to_string(i+1), "signal") );

        }
    }
        
    attribute< vector<double> > quaternion_attr { this, "quaternion", {0.1, 0.0, 0.0, 1.0}, title{"Quaternion (xyzw)"}, //note that vector<float> is not supported
        description{"Quaternion (xyzw) to be used for world rotation"},
        setter{ MIN_FUNCTION{
                float qw, qx, qy, qz; //exanding this so it's more human-readable
                qx = args[0];
                qy = args[1];
                qz = args[2];
                qw = args[3];
                quaternion = Eigen::Quaternionf(qw, qx, qy, qz); //set the member quaternion
                //set the member euler
                //Eigen::Quaternionf is a quaternion made of floats. All of this low-level linear alegbra comes from the Eigen library
                world_rotation = vraudio::WorldRotation(quaternion); //using Resonance/Eigen quaternion order (wxyz)
                return{};
        }},
        getter{ MIN_GETTER_FUNCTION{
            //this setup guarantees that we're returning the most up-to-date quaternion (the one stored as a member) which may have been modified by euler_attr
            return {quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w()}; //use jit order (xyzw)
        }},
        category {"World Rotation"}, order{2}
    };
    
    attribute< vector<double> > euler_attr { this, "euler", {0.1, 0.0, 0.0}, title{"Euler angles (order)"},
        description{"Euler angles (order) to be used for world rotation"},
        setter{
            MIN_FUNCTION{
                return {args[0], args[1], args[2]};
            }
        },
        category {"World Rotation"}, order{1}
    };
    
    void operator()(audio_bundle input, audio_bundle output) {
//        double* s = input.samples(0);
//        audio_bundle tempIn(&s, 1, input.frame_count()); //this is very nasty and inelegant.
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumSphericalHarmonics, nFrames);      // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumSphericalHarmonics, nFrames);           // resonance-style audio buffer for output
        Min2Res(input, &r_inputAudioBuffer);                            // transfer audio data from min-style audio_bundle to resonance-style audioBuffer

        hoa_rotator.Process(world_rotation, r_inputAudioBuffer, &r_outputAudioBuffer);     //rotate the buffer!

        Res2Min(r_outputAudioBuffer, &output);                          // transfer audio data from resonance-style audioBuffer to min-style audio_bundle

    }
};


MIN_EXTERNAL(rotator);
