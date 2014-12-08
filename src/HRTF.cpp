

#include <sndfile.hh>

#include "HRTF.h"
#include "Utils.h"

HRTF::~HRTF() {}

void HRTF::readFile(const std::string& fname, boost::container::vector<std::pair<float, float> >& out_samples) {
    SndfileHandle file(fname);
    sf_count_t count = file.channels() * file.frames();
    Utils::getLogger() << fname << ": " << file.frames() << std::endl;
    float* buffer = new float[count];
    sf_count_t actual_count = file.read(buffer, count);
    for (int i = 0 ; i < actual_count ; i += 2) {
        out_samples.push_back(std::pair<float, float>(buffer[i], buffer[i + 1]));
    }
    delete[] buffer;
}