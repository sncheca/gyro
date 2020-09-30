/// @file
///    @ingroup     gyro
///    @copyright    Copyright 2020 Sofia Checa
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

// Copyright 2020 Sofia Checa
// This work was funded by Yale Department of Music // Yale CCAM // Yale Blended Reality

//rotate a soundfield, using HRTFs.
// Use case: rotate the ENTIRE soundfield (ie, not to be used just to rotate one source... I mean you can if you want but this is more intended for use in conjunction with headtracking or other cases where the entire soundfield or group of sources must be rotated.

#include "c74_min.h"
#include "ambisonics/hoa_rotator.h"
#include "audio_buffer_conversion.h"
#include "ambisonics/utils.h"

// Low-level linear alegbra (quaternions, euler, rotation matrices, etc) comes from the Eigen library
#include "third_party/eigen/Eigen/Dense" //to use quaternion constructor
#include "third_party/eigen/unsupported/Eigen/EulerAngles" //to use euler conversions. Note that the one provided in Dense does not have the Euler class.

///notes about world rotations:
///This code is absolutely disgusting due to angle conversions. If this is the first object code you're reading... read something else first. This is not a friendly place to start.
//TODO: (2020.06.02) use matrix or a more elegant datatype to get rid of some of the hard-coding in here.
 
//FOR HELP VISUALISING, PLEASE SEE "Expressions of 3D Space.md"

///The rotate object can support world rotation input in the form of either quaternions or euler angles. This is because headtracking applications are likely to use quaternions, but expressive or human-controlled applictions are more likely to use Euler angles, since they are easier to visualise.
///
///As such, the euler angles and quaternions must always be kept in sync. The `quaternion` and `euler_angles` members are the "master" keeper of the most up-to-date values. They can be set by either the `quaternion_attr` or the `euler_attr`. In other words, the `quaternion_attr` setter updates both the `quaternion` member and the `euler_angles` member, and so does the `euler_attr` setter.
///
///All Resonance world rotation calculations are done using quaternions. The euler angles are only present in this top layer and in the exposure to Max, for humans to look at.
///
///For conversion to and from Euler angles, I use the unsupported Eigen EulerAngles library. Note that in this library, all angles are in radians. Thus, the `euler_angle` member stores the angles in radians. The `euler_attr` getter converts these radian values back to degrees for human exposure.
 
 ///Moreover, jit and Eigen use different angle-ordering protocols. The conversions are as follows: (1-indexed for human-readability, and for easier compatibilty with `EulerAngles` template class, see below.)
/*
 jit_triple[1] = Eigen_triple[2]
 jit_triple[2] = Eigen_triple[3]
 jit_triple[3] = Eigen_triple[1]
 
 Eigen_triple[1] = jit_triple[3]
 Eigen_triple[2] = jit_triple[1]
 Eigen_triple[3] = jit_triple[2]
 */

///The difference in angle orders also manifests itself in discussions of *rotation order*. The following table shows how a jit rotation order maps to an Eigen EulerSystem. You can easily derive these using the above conversions, but I write it out for convenience.
/*
 xyz -> EulerSystem<2,3,1>
 xzy -> EulerSystem<2,1,3>
 yxz -> EulerSystem<3,2,1>
 yzx -> EulerSystem<3,1,2>
 zxy -> EulerSystem<1,2,3>
 zyx -> EulerSystem<1,3,2>
 */

/// You will see these mappings being used in both the setters and the getters of the quaternion attribute and the euler angles attribute.

///Aside from different angle-orders for x, y, and z angles, jit puts the quaternion_w at the end of the vector while Eigen puts the quaternion_w at the beginning of the vector. This means that at times there are intermediate helper quaternions that use "hybrid-ordering", ie, xyz are ordered using jit order, but w is at the beginning, or xyz use Eigen order but w is at the end.

using namespace c74::min;

class rotator : public object<rotator>, public vector_operator<> {
private:
    //everything will be initialised in the member initialisation lists in the constructor
    const int kAmbisonicOrder;
    const int kNumSphericalHarmonics;
    const int kNumInlets;
    const int kNumOutlets;
    Eigen::Quaternionf quaternion; //keep as a member since it can be updated by either quaternion_attr or euler_attr
    Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > euler_angles;
    vraudio::WorldRotation world_rotation; //keep this as a member to avoid repeated calculations when no new spatial data.
    vraudio::HoaRotator hoa_rotator;

    std::vector< std::unique_ptr<inlet<>> >    g_inlets; //note that this must be called m_inputs!
    std::vector< std::unique_ptr<outlet<>> >   g_outlets; //must be called m_outputs

public:
    MIN_DESCRIPTION    { "Rotate a soundfield. Use argument to select ambisonic order. Ambisonic order is 1 by default." };
    MIN_TAGS           { "gyro, binaural, ambisonics, audio, headtracking" };
    MIN_AUTHOR         { "Sofia Checa" };
    MIN_RELATED        { "gyro.encoder~, gyro.binauralDecoder~, gyro.speakerDecoder~, gyro.soundfield2Stereo~, gyro.thru~" };

    //constructor that allows for number of outlets to be defined by the ambisonic order argument.
    rotator(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),    //set the default ambisonic order to 1 if there are no arguments
        kNumSphericalHarmonics(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),   //determine how many spherical harmonics there are for this order
        kNumInlets(kNumSphericalHarmonics),
        kNumOutlets(kNumSphericalHarmonics),
        hoa_rotator(kAmbisonicOrder)
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
            
        std::string helpMessage("(signal) Channel ");
        for (auto i=0; i < kNumOutlets; ++i) {
            g_inlets.push_back( std::make_unique<inlet<>>(this, helpMessage + std::to_string(i+1), "signal") ); //human labelling for channels is 1-indexed
            g_outlets.push_back( std::make_unique<outlet<>>(this, helpMessage + std::to_string(i+1), "signal") );

        }
    }
    
    attribute<symbol> rotate_order_attr {this, "rotate order", "yzx", title{"Rotate Order"},
        description{"Set the order in which rotations are applied. Default = yzx. E.G. if set to xyz, the object is first rotated around the X axis, then Y, and finally Z. Uses yzx ordering by default, because this is what jitter objects use by default in Max 8. To replicate Max 5, use zyx."},
        range{"xyz", "xzy", "yxz", "yzx", "zxy", "zyx"} //jit objects have auto as an option, but I prefer to be more explicit, and just set a default
    };
    
    attribute< vector<double> > quaternion_attr { this, "quaternion", {0.1, 0.0, 0.0, 1.0}, title{"Quaternion (xyzw)"}, //note that vector<float> is not supported
        description{"Quaternion (xyzw) to be used for world rotation"},
        setter{ MIN_FUNCTION{
            //get the jitter-ordered quaternion values from the arguments
            float jit_qx = args[0];
            float jit_qy = args[1];
            float jit_qz = args[2];
            float jit_qw = args[3];
        
            // convert from jit triples to eigen triples. w stays the same
            float eigen_qw = jit_qw;
            float eigen_qx = jit_qz;
            float eigen_qy = jit_qx;
            float eigen_qz = jit_qy;
        
            quaternion = Eigen::Quaternionf(jit_qw, jit_qx, jit_qy, jit_qz); //set the member quaternion using jit order, but with the w at the front, ie, hybrid ordering
            Eigen::Quaternionf eigen_quaternion = Eigen::Quaternionf(eigen_qw, eigen_qx, eigen_qy, eigen_qz);

            //set euler_angles member by converting quat -> mat -> euler, using the appropriate rotation order. Note that the euler_angles member will also be implicitly cast to its own type, but I cast it back to the right order in the euler_attr getter.
            auto rotateOrder = rotate_order_attr.get();
            
            if(rotateOrder == "xyz"){
                Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> > quat_euler_angles(eigen_quaternion);
                euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> > (quat_euler_angles.beta(), quat_euler_angles.gamma(), quat_euler_angles.alpha()); //this will recast
            } else if(rotateOrder == "xzy"){
                Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> > quat_euler_angles(eigen_quaternion);
                euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> > (quat_euler_angles.gamma(), quat_euler_angles.alpha(), quat_euler_angles.beta());
            } else if(rotateOrder == "yxz"){
                Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> > quat_euler_angles(eigen_quaternion);
                euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> > (quat_euler_angles.gamma(), quat_euler_angles.alpha(), quat_euler_angles.beta());
            } else if(rotateOrder == "yzx"){
                Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > quat_euler_angles(eigen_quaternion);
                euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > (quat_euler_angles.beta(), quat_euler_angles.gamma(), quat_euler_angles.alpha());
            } else if(rotateOrder == "zxy"){
                Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > quat_euler_angles(eigen_quaternion);
                euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > (quat_euler_angles.beta(), quat_euler_angles.gamma(), quat_euler_angles.alpha());
            } else if(rotateOrder == "zyx"){
                Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > quat_euler_angles(eigen_quaternion);
                euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > (quat_euler_angles.gamma(), quat_euler_angles.alpha(), quat_euler_angles.beta());
            }
            world_rotation = vraudio::WorldRotation(quaternion);
            return{};
        }},
        getter{ MIN_GETTER_FUNCTION{
            //get the most up-to-date quaternion (the one stored as a member) which may have been modified by euler_attr
            return {quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w()}; //use jit order (xyzw)
        }},
    };
    
    attribute< vector<double> > euler_attr { this, "euler", {0.0, 0.0, 0.0}, title{"Euler angles (xyz)"},
        description{"Euler angles (xyz) to be used for world rotation"},
        setter{
            MIN_FUNCTION{
                //note: I split this up to make it human readable.
                //get the jitter-ordered angles from the arguments
                float jit_x = vraudio::kRadiansFromDegrees * float(args[0]);  //euler angles are stored internally as radians
                float jit_y = vraudio::kRadiansFromDegrees * float(args[1]);
                float jit_z = vraudio::kRadiansFromDegrees * float(args[2]);
                
                // convert from jit triples to eigen triples. These are in RADIANS and must be floats lol
                float eigen_x = jit_z;
                float eigen_y = jit_x;
                float eigen_z = jit_y;
                
                auto rotateOrder = rotate_order_attr.get();
                
                //set euler_angles member using the appropriate rotation order. Note that the euler_angles member will also be implicitly cast to its own type, but I cast it back to the right order in the euler_attr getter.
                Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > quat_euler_angles;
                if(rotateOrder == "xyz"){
                    //assign the euler member (no bearing on sound, just for keeping track internally). May be able to move this out. Decide after finishing other direction
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> > (jit_y, jit_z, jit_x);
                    quat_euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> >(eigen_y, eigen_z, eigen_x);
                } else if(rotateOrder == "xzy"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> > (jit_y, jit_x, jit_z);
                    quat_euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> >(eigen_y, eigen_x, eigen_z);
                } else if(rotateOrder == "yxz"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> > (jit_z, jit_y, jit_x);
                    quat_euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> >(eigen_z, eigen_y, eigen_x);
                } else if(rotateOrder == "yzx"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > (jit_z, jit_x, jit_y);
                    quat_euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >(eigen_z, eigen_x, eigen_y);
                } else if(rotateOrder == "zxy"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > (jit_x, jit_y, jit_z);
                    quat_euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >(eigen_x, eigen_y, eigen_z);
                } else if(rotateOrder == "zyx"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > (jit_x, jit_z, jit_y);
                    quat_euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> >(eigen_x, eigen_z, eigen_y);
                }
                
                Eigen::Quaternionf eq(quat_euler_angles);
                quaternion = Eigen::Quaternionf(eq.w(), eq.y(), eq.z(), eq.x()); //back to jitter order for xyz
                quaternion.normalize();
//                quaternion = euler_angles;
//                quaternion = static_cast<Eigen::Quaternionf>(euler_angles); //set the member quaternion
                world_rotation = vraudio::WorldRotation(quaternion); //using Resonance/Eigen quaternion order (wxyz)
                return {};
            }
        },
        getter {
            MIN_GETTER_FUNCTION{
                //get the most up-to-date euler angles (the one stored as a member) which may have been modified by quaternion_attr
                auto rotateOrder = rotate_order_attr.get();
                
                //note that I am using the mapping between jit order and Eigen order, explained at the top
                if(rotateOrder == "xyz"){ //DIFF, works
                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                            vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                            vraudio::kDegreesFromRadians * recast_euler_angles.beta()};
                } else if(rotateOrder == "xzy"){ //match, ooo
                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
                } else if(rotateOrder == "yxz"){ //match, ooo
                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.alpha()};
                } else if(rotateOrder == "yzx"){ //DIFF, works
                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.alpha()};
                } else if(rotateOrder == "zxy"){ //match, works
                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
                } else if(rotateOrder == "zyx"){ //match, ooo
                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.beta()};
                } else {
                    return {}; //silence warning
                }
            }
        },
    };
    
    void operator()(audio_bundle input, audio_bundle output) {
//        double* s = input.samples(0);
//        audio_bundle tempIn(&s, 1, input.frame_count()); //this is very nasty and inelegant.
        auto nFrames = input.frame_count();
        vraudio::AudioBuffer r_inputAudioBuffer(kNumSphericalHarmonics, nFrames);      // resonance-style audio buffer for input
        vraudio::AudioBuffer r_outputAudioBuffer(kNumSphericalHarmonics, nFrames);     // resonance-style audio buffer for output
        pita::Min2Res(input, &r_inputAudioBuffer);   // transfer audio data from min-style audio_bundle to resonance-style audioBuffer
        
        //in my opinion, this is one of Resonance's worse designs...I think the rotator should do this internally.
        if (hoa_rotator.Process(world_rotation, r_inputAudioBuffer, &r_outputAudioBuffer)){ //rotate the buffer!
            pita::Res2Min(r_outputAudioBuffer, &output);  // transfer audio data from resonance-style audioBuffer to min-style audio_bundle
        } else {
            pita::Res2Min(r_inputAudioBuffer, &output); //if the difference is too small to do a rotation, just send it out the same.
        }


    }
};


MIN_EXTERNAL(rotator);
