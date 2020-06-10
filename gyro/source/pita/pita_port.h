/*
Copyright 2020 Sofia Checa, Yale CCAM // Yale Blended Reality // Yale Department of Music

audio buffer conversion functions. Following the paradigm of Min, functions are collapsed into .h files instead of cpp files.
 
Derived class for inlets and outlets. The only difference is that the description is modifiable. I could have directly modified the min_api code, but I'd prefer to keep that intact and build over it, because it's easier to manage submodules and allow for updates to the min_api
*/

#ifndef PITA_PORT_H_
#define PITA_PORT_H_

#include "c74_min.h"

using namespace c74::min;

class pitaOutlet : public outlet<> {
public:
    pitaOutlet(object_base* an_owner, const std::string& a_description, const std::string& a_type = "", size_t an_atom_count = 1): outlet(an_owner, a_description, a_type, an_atom_count){}
    pitaOutlet(object_base* an_owner, const std::string& a_description, size_t an_atom_count, const std::string& a_type = "") : pitaOutlet(an_owner, a_description, a_type, an_atom_count){}
    void setDescription(string s){
        m_description = s;
        return;
    }
};

#endif  // PITA_PORT_H_




