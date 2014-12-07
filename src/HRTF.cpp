

#include <sndfile.hh>

#include "HRTF.h"
#include "Utils.h"

HRTF::~HRTF() {}

void HRTF::readFile(const std::string& fname, boost::container::vector<float>& list) {
    SndfileHandle file(fname);
    sf_count_t count = file.channels() * file.frames();
    Utils::getLogger() << fname << ": " << file.frames() << std::endl;
    float* buffer = new float[count];
    sf_count_t actual_count = file.read(buffer, count);
    for (int i = 0 ; i < actual_count ; ++i) {
        list.push_back(buffer[i]);
    }
    delete[] buffer;
}