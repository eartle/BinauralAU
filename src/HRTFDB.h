
#pragma once

#include <string>

#include <boost/container/vector.hpp>

#include "HRTF.h"

using namespace boost;
using namespace container;

class HRTFDB : public HRTF {
public:
    HRTFDB(const std::string& status_id, const std::string& status);
    
private:
    const std::pair<vector<float>, vector<float> >& getHRTF(float elevation, float angle, bool& swap) const;
    
private:
    vector<std::pair<vector<float>, vector<float> > > mAllHRTFs;
};