
#pragma once

#include <boost/container/vector.hpp>

#include "HRTF.h"

class Diffuse : public HRTF {
public:
    Diffuse();
    
private:
    const boost::container::vector<float>& getHRTF(float elevation, float angle, bool& swap) const;
    int getElevationIndex(float elevation) const;
    int getAngleIndex(float elevation, float angle) const;
    
private:
    boost::container::vector<boost::container::vector<float> > mHRTFs[14];
};