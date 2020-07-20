/*
Copyright 2020 Sofia Checa, Yale CCAM // Yale Blended Reality // Yale Department of Music

Following the paradigm of Min, pita functions are collapsed into .h files instead of cpp files.
 
Derived class for inlets and outlets. The only difference is that the description is modifiable. I could have directly modified the min_api code, but I'd prefer to keep that intact and build over it, because it's easier to manage submodules and allow for updates to the min_api
*/

#ifndef PITA_PORT_H_
#define PITA_PORT_H_

#include "c74_min.h"

using namespace c74::min;

namespace pita{

//expects i to be 0-indexed
std::string generatePortAngleLabel(int i, std::vector<vraudio::SphericalAngle>& angles){
    //human labelling for channels is 1-indexed
    std::string portAngleLabel = "(signal) Channel " + std::to_string(i+1) + " (" + std::to_string(int(angles.at(i).azimuth()*vraudio::kDegreesFromRadians)) + "°, " + std::to_string(int(angles.at(i).elevation()*vraudio::kDegreesFromRadians)) + "°)";
    return portAngleLabel;
}

class p_inlet : public inlet<>{
public:
    p_inlet(object_base* an_owner, const std::string& a_description, const std::string& a_type = ""): inlet (an_owner, a_description, a_type){}
    p_inlet(object_base* an_owner, const std::string& a_description, attribute_base& an_attribute_to_which_to_map_audio_input, const std::string& a_type = "") : inlet(an_owner, a_description, an_attribute_to_which_to_map_audio_input, a_type){}
    void setDescription(std::string s){
        m_description = s;
        return;
    }
};

class p_outlet : public outlet<> {
public:
    p_outlet(object_base* an_owner, const std::string& a_description, const std::string& a_type = "", size_t an_atom_count = 1) : outlet(an_owner, a_description, a_type, an_atom_count){}
    p_outlet(object_base* an_owner, const std::string& a_description, size_t an_atom_count, const std::string& a_type = "") : p_outlet(an_owner, a_description, a_type, an_atom_count){}
    void setDescription(string s){
        m_description = s;
        return;
    }
};

} //namespace pita

#endif  // PITA_PORT_H_




