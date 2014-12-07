
#include <string>
#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>

#include <sndfile.hh>

#include "Fir.h"
#include "Utils.h"

#define PAST_INPUT_MAX_SIZE 256

void Fir::readFile(const std::string& fname, boost::container::vector<float>& list) {
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

Fir::Fir(Channel inputChannel)
    :mElevation(ParamElevationDefaultValue),
        mAngle(ParamAngleDefaultValue),
        mInputChannel(inputChannel)
{
    std::string path = Utils::getResourcePath();
    Utils::getLogger() << path << std::endl;
    std::string filename_format = "/H%de%03da.wav";
    
    for (int elev_index = 0 ; elev_index < 14 ; ++elev_index) {
        int elevation = (elev_index - 4) * 10;
        
        for (int angle = 0 ; angle <= 180 ; ++angle) {
            // try finding a file for every angle
            std::string filename = path + (boost::format(filename_format) % elevation % angle).str();
            if (boost::filesystem::exists(filename)) {
                boost::container::vector<float> angle_samples;
                readFile(filename, angle_samples);
                mHRTFs[elev_index].push_back(angle_samples);
            }
        }
        
        Utils::getLogger() << boost::format("elev: %1% size: %2%.") % elev_index % mHRTFs[elev_index].size() << std::endl;
    }
}

float Fir::getOutput(Channel channel) const {
    float output = 0;
    
    if (mAngle > 180) {
        // we're over 180º so swap the channels
        if (channel == ChannelLeft)
            channel = ChannelRight;
        else if (channel == ChannelRight)
            channel = ChannelLeft;
    }
    
    const boost::container::vector<float>& hrtf = mHRTFs[getElevationIndex()][getAngleIndex()];
    
    {
        static int lastAngleIndex = 0;
        static int lastElevationIndex = 0;
        
        if ((getAngleIndex() != lastAngleIndex)
            || (lastElevationIndex != getElevationIndex())) {
            lastAngleIndex = getAngleIndex();
            lastAngleIndex = getElevationIndex();
            
            Utils::getLogger() << boost::format("getOutput elev: %1% angle: %2% %3% %4%.") % getElevationIndex() % getAngleIndex() % hrtf.size() % mPastInputs.size() << std::endl;
        }
    }
    
    // The science bit: a discrete convolution
    // the output is the
    for (int i = 0 ; (i < (hrtf.size() / 2)) && (i < mPastInputs.size()) ; ++i) {
        // the samples are interleaved (left is every other starting at 0)
        //                             (right is every other starting at 1)
        output += mPastInputs[i] * hrtf[((channel == ChannelLeft) ? i : i + 1) * 2];
    }
    
	return output;
}

void Fir::putNextInput(const float left, const float right) {
    if (mInputChannel == ChannelMix) {
        mPastInputs.push_front((left + right) / 2);
    } else if (mInputChannel == ChannelLeft) {
        mPastInputs.push_front(left);
    } else if (mInputChannel == ChannelRight) {
        mPastInputs.push_front(right);
    }
    
    if (mPastInputs.size() > PAST_INPUT_MAX_SIZE)
        mPastInputs.pop_back();
}

float Fir::getElevation() const {
	return mElevation;
}

int Fir::getElevationIndex() const {
    // elevation goes from -40º to 90º
    //                      0   to 13
    return boost::math::round((getElevation() + 40.0f) / 10.0f);
}

float Fir::getAngle() const {
	return mAngle;
}

int Fir::getAngleIndex() const {
    // angle goes from 0º to 360º
    float angle = fmod(getAngle(), 180.0f);
    // angle goes from 0º to 180º
    //                 0  to elevationFidelity(int elevation)
    return boost::math::round((mHRTFs[getElevationIndex()].size() - 1) * (angle / 180.0f));
}

void Fir::setElevation(float elevation) {
	mElevation = elevation;
}

void Fir::setAngle(float angle) {
	mAngle = angle;
}
