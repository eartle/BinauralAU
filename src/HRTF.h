
#pragma once

#include <boost/container/vector.hpp>

class HRTF {
public:
    virtual ~HRTF();
    
    virtual const std::pair<boost::container::vector<float>, boost::container::vector<float> >& getHRTF(float elevation, float angle, bool& swap) const = 0;
    
protected:
    void readFile(const std::string& fname, std::pair<boost::container::vector<float>, boost::container::vector<float> >& out_samples);
};