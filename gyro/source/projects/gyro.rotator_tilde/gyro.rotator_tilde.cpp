/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

///Copyright Sofia Checa 2020.

//binaurally render a soundfield, using HRTFs

#include "c74_min.h"
#include "ambisonics/hoa_rotator.h"
#include "audio_buffer_conversion.h"

using namespace c74::min;

class rotator : public object<rotator>, public vector_operator<> {
private:
    //everything will be initialised in the member initialisation lists in the constructor
    const int kAmbisonicOrder;
    const int kNumSphericalHarmonics;
    const int kNumInlets;
    const int kNumOutlets;
    vraudio::WorldRotation world_rotation;
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
        kNumSphericalHarmonics((kAmbisonicOrder+1)*(kAmbisonicOrder+1)),   //TODO turn this into a function. see hoa_rotator.cc for GetNumNthOrder
        kNumInlets(kNumSphericalHarmonics + 1), //extra inlet for the angle control
        kNumOutlets(kNumSphericalHarmonics),
        hoa_rotator(kAmbisonicOrder)
        {
        
        //inlet handling
        //most max objects do not complain about extra arguments, so I don't either.
        if(!args.empty() && (int(args[0]) > 3 || int(args[0]) < 1)){
            error("This package currently supports only 1st, 2nd, and 3rd order ambisonics.");
        }
        std::string inletHelpMessage("(signal) Channel ");
        for (auto i=0; i < kNumOutlets; ++i) {
            m_inlets.push_back( std::make_unique<inlet<>>(this, inletHelpMessage + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
            m_outlets.push_back( std::make_unique<outlet<>>(this, inletHelpMessage + std::to_string(i+1), "signal") );

        }
        //inlet for angle data
        m_inlets.push_back( std::make_unique<inlet<>>(this, "(float) quaternion xyzw in", "float") );
    }
    
    message<> updateRotationAngle { this, "list", "message for world rotation",
        MIN_FUNCTION {
            float qw, qx, qy, qz;
            cout << "inside update rotation message" << endl;
//            if (inlet == kNumInlets-1){ //last inlet
//                if(args[0] == "quat"){
                    //TODO error check for number of args
                    //NOTE: the order for the inlet is designed to match the order used by jit objects such as jit.euler2quat
                    qx = args[0];
                    qy = args[1];
                    qz = args[2];
                    qw = args[3];
                    world_rotation = vraudio::WorldRotation(qw, qx, qy, qz); //note different order
//                }
//            }
            return {};
        }
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