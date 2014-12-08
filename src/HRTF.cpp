

#include <sndfile.hh>

#include "HRTF.h"
#include "Utils.h"

using namespace boost;
using namespace container;

HRTF::~HRTF() {}

void HRTF::readFile(const std::string& fname, std::pair<vector<float>, vector<float> >& out_samples) {
    SndfileHandle file(fname);
    sf_count_t count = file.channels() * file.frames();
    Utils::getLogger() << fname << ": " << file.frames() << std::endl;
    float* buffer = new float[count];
    sf_count_t actual_count = file.read(buffer, count);
    
    vector<float> left;
    vector<float> right;
    
    for (int i = 0 ; i < actual_count ; i += 2) {
        left.push_back(buffer[i]);
        right.push_back(buffer[i + 1]);
    }
    
    out_samples.first = left;
    out_samples.second = right;
    
    delete[] buffer;
}