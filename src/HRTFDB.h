
#pragma once

#include <string>

#include <boost/container/vector.hpp>

#include "HRTF.h"

class HRTFDB : public HRTF {
public:
    HRTFDB(const std::string& status_id, const std::string& status);
    
private:
    const boost::container::vector<float>& getHRTF(float elevation, float angle, bool& swap) const;
    
private:
    boost::container::vector<boost::container::vector<float> > mAllHRTFs;
};