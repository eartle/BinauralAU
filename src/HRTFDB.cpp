
#include <boost/format.hpp>

#include "HRTFDB.h"
#include "Utils.h"

HRTFDB::HRTFDB(const std::string& subject_id, const std::string& status) {
    int radius = 195;
    int azimuth = 0;
    int elevation = 0;
    
    std::string path = Utils::getResourcePath() + "/hrtfdb";
    std::string file_format = "/IRC_%s_%s_R%04d_T%03d_P%03d.wav";
    std::string filename = path + (boost::format(file_format) % subject_id % status % radius % azimuth % elevation).str();
    
    boost::container::vector<std::pair<float, float> > samples;
    readFile(filename, samples);
    mAllHRTFs.push_back(samples);
}

const boost::container::vector<std::pair<float, float> >& HRTFDB::getHRTF(float elevation, float angle, bool& swap) const {
    swap = false;
    return mAllHRTFs[0];
}