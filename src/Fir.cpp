
#include <string>
#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>

#include "Fir.h"
#include "Utils.h"
#include "Diffuse.h"

#define PAST_INPUT_MAX_SIZE 256

Fir::Fir(Channel inputChannel)
    :mInputChannel(inputChannel),
        mElevation(ParamElevationDefaultValue),
        mAngle(ParamAngleDefaultValue)
{
    mHRTF = new Diffuse();
}

Fir::~Fir() {
    delete mHRTF;
}

float Fir::getOutput(Channel channel) const {
    float output = 0;
    
    bool swap;
    const boost::container::vector<float>& hrtf = mHRTF->getHRTF(getElevation(), getAngle(), swap);
    
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

float Fir::getAngle() const {
	return mAngle;
}

void Fir::setElevation(float elevation) {
	mElevation = elevation;
}

void Fir::setAngle(float angle) {
	mAngle = angle;
}
