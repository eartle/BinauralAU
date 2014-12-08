
#pragma once

#include <boost/container/vector.hpp>

#include "HRTF.h"

using namespace boost;
using namespace container;

class Diffuse : public HRTF {
public:
    Diffuse();
    
private:
    const std::pair<vector<float>, vector<float> >& getHRTF(float elevation, float angle, bool& swap) const;
    int getElevationIndex(float elevation) const;
    int getAngleIndex(float elevation, float angle) const;
    
private:
    vector<std::pair<vector<float>, vector<float> > > mHRTFs[14];
};