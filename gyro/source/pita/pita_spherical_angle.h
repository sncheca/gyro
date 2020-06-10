/*
Copyright 2020 Sofia Checa, Yale CCAM // Yale Blended Reality // Yale Department of Music

Following the paradigm of Min, pita functions are collapsed into .h files instead of cpp files.
 
extra functionality related to spherical angles
 */

#ifndef PITA_SPHERICAL_ANGLES_H_
#define PITA_SPHERICAL_ANGLES_H_

#include "c74_min.h"

using namespace c74::min;

namespace pita{

// Convert sphericalAngles vector to an interleaved list of speaker angles (°) in axis-angle in the form [1 <azimuth1> <elevation1> 2 <azimuth2> <elevation2> ...]
vector<atom> sa2atoms(const std::vector<vraudio::SphericalAngle>& other){
    vector<atom> a;
    for(int i = 0; i<other.size(); i++){
        a.push_back(i+1); //change to human indexing
        a.push_back(other.at(i).azimuth()*vraudio::kDegreesFromRadians);
        a.push_back(other.at(i).elevation()*vraudio::kDegreesFromRadians);
    }
    return a;
}

} //namespace pita

#endif  // PITA_SPHERICAL_ANGLES_H_




