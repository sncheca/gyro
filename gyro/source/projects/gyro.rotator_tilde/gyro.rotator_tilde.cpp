/// @file
///    @ingroup     minexamples
///    @copyright    Copyright 2018 The Min-DevKit Authors. All rights reserved.
///    @license    Use of this source code is governed by the MIT License found in the License.md file.

///Copyright Sofia Checa 2020.
///This work was jointly funded by the Yale CCAM, the Yale Blended Reality Grant, and the Yale Department of Music.

//rotate a soundfield, using HRTFs

#include "c74_min.h"
#include "ambisonics/hoa_rotator.h"
#include "audio_buffer_conversion.h"
#include "ambisonics/utils.h"

// Low-level linear alegbra (quaternions, euler, rotation matrices, etc) comes from the Eigen library
#include "third_party/eigen/Eigen/Dense" //to use quaternion constructor
#include "third_party/eigen/unsupported/Eigen/EulerAngles" //to use euler conversions. Note that the one provided in Dense does not have the Euler class.

/* notes about world rotations
 
The rotate object can support world rotation input in the form of either quaternions or euler angles. This is because headtracking applications are likely to use quaternions, but expressive or human-controlled applictions are more likely to use Euler angles, since they are easier to visualise.
 As such, the euler angles and quaternions must always be kept in sync. The `quaternion` and `euler_angles` members are the "master" keeper of the most up-to-date values. They can be set by either the `quaternion_attr` or the `euler_attr`.
 All Resonance world rotation calculations are done using quaternions. The euler angles are only present in this top layer and in the exposure to Max.
 For conversion to and from Euler angles, I use the unsupported Eigen EulerAngles library. Note that in this library, all angles are in degrees. Thus, the `euler_angle` member stores the angles in radians. The `euler_attr` getter converts these radian values back to degrees for human exposure.

 */

using namespace c74::min;

//enum RotateOrder {
//    XYZ, XZY, YXZ, YZX, ZXY, ZYX
//};

class rotator : public object<rotator>, public vector_operator<> {
private:
    //everything will be initialised in the member initialisation lists in the constructor
    const int kAmbisonicOrder;
    const int kNumSphericalHarmonics;
    const int kNumInlets;
    const int kNumOutlets;
    Eigen::Quaternionf quaternion; //keep this as a member since it can be updated by either quaternion_attr or euler_attr
//    RotateOrder rotateOrder = ZXY;
    Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > euler_angles;
    vraudio::WorldRotation world_rotation; //keep this as a member to avoid repeated calculations
    vraudio::HoaRotator hoa_rotator;

    std::vector< std::unique_ptr<inlet<>> >    m_inlets; //note that this must be called m_inputs!
    std::vector< std::unique_ptr<outlet<>> >   m_outlets; //must be called m_outputs

public:
    MIN_DESCRIPTION    { "Rotate a soundfield. Use argument to select ambisonic order. Ambisonic order is 1 by default." };
    MIN_TAGS           { "gyro, encoder, binauralDecoder, ambisonics, audio" };
    MIN_AUTHOR         { "Cycling '74" };
    MIN_RELATED        { "index~, buffer~, wave~" };

//    typedef Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > GyroEulerAngles;
    /// constructor that allows for number of outlets to be defined by the ambisonic order argument.
    rotator(const atoms& args = {})
      : kAmbisonicOrder(args.empty() ? 1: int(args[0])),    //set the default ambisonic order to 1 if there are no arguments
        kNumSphericalHarmonics(vraudio::GetNumPeriphonicComponents(kAmbisonicOrder)),   //determine how many spherical harmonics there are for this order
        kNumInlets(kNumSphericalHarmonics),
        kNumOutlets(kNumSphericalHarmonics),
        hoa_rotator(kAmbisonicOrder)
        {
            
        //this shows that casting works the way I thought it did
//        Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >  a1(0*vraudio::kRadiansFromDegrees, 45*vraudio::kRadiansFromDegrees, 0*vraudio::kRadiansFromDegrees);
//        cout << a1.alpha()*vraudio::kDegreesFromRadians << " " << a1.beta()*vraudio::kDegreesFromRadians << " " << a1.gamma()*vraudio::kDegreesFromRadians << endl;
//
//        Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >  a2(0*vraudio::kRadiansFromDegrees, 90*vraudio::kRadiansFromDegrees, 0*vraudio::kRadiansFromDegrees);
//        cout << a2.alpha()*vraudio::kDegreesFromRadians << " " << a2.beta()*vraudio::kDegreesFromRadians << " " << a2.gamma()*vraudio::kDegreesFromRadians << endl;
//
//        Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > a3  = (Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >)a2;
//        cout << a3.alpha()*vraudio::kDegreesFromRadians << " " << a3.beta()*vraudio::kDegreesFromRadians << " " << a3.gamma()*vraudio::kDegreesFromRadians << endl;
//
//        Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > a4 = a3;
//        cout << a4.alpha()*vraudio::kDegreesFromRadians << " " << a4.beta()*vraudio::kDegreesFromRadians << " " << a4.gamma()*vraudio::kDegreesFromRadians << endl;
//
//        Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >  a5(90*vraudio::kRadiansFromDegrees, 0*vraudio::kRadiansFromDegrees, 0*vraudio::kRadiansFromDegrees);
//        cout << a5.alpha()*vraudio::kDegreesFromRadians << " " << a5.beta()*vraudio::kDegreesFromRadians << " " << a5.gamma()*vraudio::kDegreesFromRadians << endl;
//
//        Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >  a6(10*vraudio::kRadiansFromDegrees, 20*vraudio::kRadiansFromDegrees,30*vraudio::kRadiansFromDegrees);
//        cout << a6.alpha()*vraudio::kDegreesFromRadians << " " << a6.beta()*vraudio::kDegreesFromRadians << " " << a6.gamma()*vraudio::kDegreesFromRadians << endl;
//        Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3>> a7 = a6;
//        cout << a7.alpha()*vraudio::kDegreesFromRadians << " " << a7.beta()*vraudio::kDegreesFromRadians << " " << a7.gamma()*vraudio::kDegreesFromRadians << endl;
//
//        Eigen::Quaternionf q1 = a1;
//        print(q1);
//
//        Eigen::Quaternionf q2 = a2;
//        print(q2);
//
//        Eigen::Quaternionf q3 = a3;
//        print(q3);
//
//        Eigen::Quaternionf q4 = a4;
//        print(q4);
//
//        Eigen::Quaternionf q5 = a5;
//        print(q5);
//
//        Eigen::Quaternionf q6 = a6;
//        print(q6);
//
//        Eigen::Quaternionf q7 = a7;
//        print(q7);
        
            
        //jit angles
        int jx = -86;
        int jy = 12;
        int jz = 43;
        
        //don't convert
//        int lex = jx; //43
//        int ley = jy; //-86
//        int lez = jz; //12
            
        // convert from jit triples to eigen triples
        int lex = jz; //43
        int ley = jx; //-86
        int lez = jy; //12
            
        Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >  a1(lex*vraudio::kRadiansFromDegrees, ley*vraudio::kRadiansFromDegrees, lez*vraudio::kRadiansFromDegrees);
        cout << a1.angles().transpose()*vraudio::kDegreesFromRadians << endl;
        Eigen::Quaternionf eq1 = Eigen::Quaternionf(a1);
        Eigen::Quaternionf fq1 = Eigen::Quaternionf(eq1.w(), eq1.y(), eq1.z(), eq1.x());
        print(fq1);
//        Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > a1back(q1);
//        cout << a1back.angles().transpose()*vraudio::kDegreesFromRadians << endl;
//        Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > a1backchange(q1);
//        cout << a1backchange.angles().transpose()*vraudio::kDegreesFromRadians << endl;

        
        //note that the xyz order is the same as the 123 order. This should work with zyx
        Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> >  a2(lex*vraudio::kRadiansFromDegrees, lez*vraudio::kRadiansFromDegrees, ley*vraudio::kRadiansFromDegrees);
        cout << a2.angles().transpose()*vraudio::kDegreesFromRadians << endl;
        Eigen::Quaternionf eq2 = Eigen::Quaternionf(a2);
        Eigen::Quaternionf fq2 = Eigen::Quaternionf(eq2.w(), eq2.y(), eq2.z(), eq2.x());
        print(fq2);
            
        //this should work with yzx
        Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >  a3(lez*vraudio::kRadiansFromDegrees, lex*vraudio::kRadiansFromDegrees, ley*vraudio::kRadiansFromDegrees);
        cout << a3.angles().transpose()*vraudio::kDegreesFromRadians << endl;
        Eigen::Quaternionf eq3 = Eigen::Quaternionf(a3);
//        Eigen::Quaternionf fq3 = Eigen::Quaternionf(eq3.w(), eq3.x(), eq3.y(), eq3.z()); //do not reorder
        Eigen::Quaternionf fq3 = Eigen::Quaternionf(eq3.w(), eq3.y(), eq3.z(), eq3.x()); //reorder back to jit
        print(fq3);
            
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
    void print(Eigen::Quaternionf q){
        cout << q.x() << "____" << q.y() << "____" << q.z() << "____" << q.w() << endl;
//        cout << q.z() << "____" << q.x() << "____" << q.y() << "____" << q.w() << endl;
        
        //convert from Eigen-style quaternion to jitter style quaternion.
//        cout << q.y() << "____" << q.z() << "____" << q.x() << "____" << q.w() << endl;


    }
    
    //TODO grow this, use enum map
    attribute<symbol> rotate_order_attr {this, "rotate order", "zxy", title{"Rotate Order"},
        description{"Set the order in which rotations are applied."}, //TODO copy description from jit
        range{"xyz", "xzy", "yxz", "yzx", "zxy", "zyx"}
    };
        
    attribute< vector<double> > quaternion_attr { this, "quaternion", {0.1, 0.0, 0.0, 1.0}, title{"Quaternion (xyzw)"}, //note that vector<float> is not supported
        description{"Quaternion (xyzw) to be used for world rotation"},
        setter{ MIN_FUNCTION{
                float qw, qx, qy, qz; //expanding this so it's more human-readable
                qx = args[0];
                qy = args[1];
                qz = args[2];
                qw = args[3];
            
//                qx = args[2];
//                qy = args[0];
//                qz = args[1];
//                qw = args[3];
            
                quaternion = Eigen::Quaternionf(qw, qx, qy, qz); //set the member quaternion using Resonance/Eigen quaternion order (wxyz)
//                Eigen::Quaternionf reordered_quaternion = Eigen::Quaternionf(qw, qy, qz, qx); //231
//                Eigen::Quaternionf reordered_quaternion = Eigen::Quaternionf(qw, qz, qx, qy); //312

                //set euler_angles member by converting quat -> mat -> euler, using the appropriate rotation order. Note that the euler_angles member will also be implicitly cast to its own type, but I cast it back to the right order in the euler_attr getter.
                auto rotateOrder = rotate_order_attr.get();
//                cout << rotateOrder << endl;
                if(rotateOrder == "xyz"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >(quaternion.toRotationMatrix());
                } else if(rotateOrder == "xzy"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> >(quaternion.toRotationMatrix());
                } else if(rotateOrder == "yxz"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> >(quaternion.toRotationMatrix());
                } else if(rotateOrder == "yzx"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> >(quaternion.toRotationMatrix());
                } else if(rotateOrder == "zxy"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >(quaternion.toRotationMatrix());
                } else if(rotateOrder == "zyx"){
                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> >(quaternion.toRotationMatrix());
                }
            
//                if(rotateOrder == "xyz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "xzy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "yxz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "yzx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "zxy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "zyx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> >(quaternion.toRotationMatrix());
//                }
            
//                if(rotateOrder == "xyz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "xzy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "yxz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "yzx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "zxy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> >(quaternion.toRotationMatrix());
//                } else if(rotateOrder == "zyx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> >(quaternion.toRotationMatrix());
//                }
            
                world_rotation = vraudio::WorldRotation(quaternion);
                return{};
        }},
        getter{ MIN_GETTER_FUNCTION{
            //get the most up-to-date quaternion (the one stored as a member) which may have been modified by euler_attr
            return {quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w()}; //use jit order (xyzw)
        }},
    };
    
    attribute< vector<double> > euler_attr { this, "euler", {0.1, 0.0, 0.0}, title{"Euler angles (order)"},
        description{"Euler angles (order) to be used for world rotation"},
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
//                cout << rotateOrder << endl;
                //set euler_angles member using the appropriate rotation order. Note that the euler_angles member will also be implicitly cast to its own type, but I cast it back to the right order in the euler_attr getter.
                
//                if(rotateOrder == "xyz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >(ex, ey, ez);
//                } else if(rotateOrder == "xzy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> >(ex, ey, ez);
//                } else if(rotateOrder == "yxz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> >(ex, ey, ez);
//                } else if(rotateOrder == "yzx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> >(ex, ey, ez);
//                } else if(rotateOrder == "zxy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >(ex, ey, ez);
//                } else if(rotateOrder == "zyx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> >(ex, ey, ez);
//                }
//                remapped ordering
                
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
                
                //remapped ordering, other direction
//                if(rotateOrder == "xyz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> >(ex, ey, ez);
//                } else if(rotateOrder == "xzy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> >(ex, ey, ez);
//                } else if(rotateOrder == "yxz"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> >(ex, ey, ez);
//                } else if(rotateOrder == "yzx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> >(ex, ey, ez);
//                } else if(rotateOrder == "zxy"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> >(ex, ey, ez);
//                } else if(rotateOrder == "zyx"){
//                    euler_angles = Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> >(ex, ey, ez);
//                }
                Eigen::Quaternionf eq(quat_euler_angles);
                eq.normalize();
                quaternion = Eigen::Quaternionf(eq.w(), eq.y(), eq.z(), eq.x()); //back to jitter order for xyz

//                quaternion = euler_angles;
//                quaternion = static_cast<Eigen::Quaternionf>(euler_angles); //set the member quaternion
                world_rotation = vraudio::WorldRotation(quaternion); //using Resonance/Eigen quaternion order (wxyz)
                return {};
            }
        },
        getter {
            MIN_GETTER_FUNCTION{
                //get the most up-to-date euler angles (the one stored as a member) which may have been modified by quaternion_attr
//                return {vraudio::kDegreesFromRadians * euler_angles.alpha(),
//                vraudio::kDegreesFromRadians * euler_angles.beta(),
//                vraudio::kDegreesFromRadians * euler_angles.gamma()};
                auto rotateOrder = rotate_order_attr.get();
                
                //recast the euler angles to the correct euler system, making use of the EulerAngles operator=
//                if(rotateOrder == "xyz"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                            vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                            vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "xzy"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "yxz"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "yzx"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "zxy"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "zyx"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else {
//                    return {}; //silence warning
//                }
                
                //remapped order (use this one!)
                if(rotateOrder == "xyz"){
                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                            vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                            vraudio::kDegreesFromRadians * recast_euler_angles.beta()};
                } else if(rotateOrder == "xzy"){
                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
                } else if(rotateOrder == "yxz"){
                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.alpha()};
                } else if(rotateOrder == "yzx"){
                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.alpha()};
                } else if(rotateOrder == "zxy"){
                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
                } else if(rotateOrder == "zyx"){
                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > recast_euler_angles = euler_angles;
                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma(),
                        vraudio::kDegreesFromRadians * recast_euler_angles.beta()};
                } else {
                    return {}; //silence warning
                }
                
                //remapped order, other direction
//                if(rotateOrder == "xyz"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,1,2> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                            vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                            vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "xzy"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<3,2,1> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "yxz"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,3,2> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "yzx"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<1,2,3> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "zxy"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,3,1> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else if(rotateOrder == "zyx"){
//                    Eigen::EulerAngles<float, Eigen::EulerSystem<2,1,3> > recast_euler_angles = euler_angles;
//                    return {vraudio::kDegreesFromRadians * recast_euler_angles.alpha(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.beta(),
//                        vraudio::kDegreesFromRadians * recast_euler_angles.gamma()};
//                } else {
//                    return {}; //silence warning
//                }
                
            }
        },
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
