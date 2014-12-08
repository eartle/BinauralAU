
#include <string>
#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>

#include "Fir.h"
#include "Utils.h"
#include "Diffuse.h"
#include "HRTFDB.h"

#define PAST_INPUT_MAX_SIZE 4096

Fir::Fir(Channel inputChannel)
    :mInputChannel(inputChannel),
        mInputBuffer(PAST_INPUT_MAX_SIZE),
        mElevation(ParamElevationDefaultValue),
        mAngle(ParamAngleDefaultValue)
{
    mHRTF = new Diffuse();
    //mHRTF = new HRTFDB("1002", "C");
}

Fir::~Fir() {
    delete mHRTF;
}

void Fir::process(float inLeft, float inRight,
                     float& outLeft, float& outRight) {
    outLeft = 0;
    outRight = 0;
    
    if (mInputChannel == ChannelMix) {
        mInputBuffer.push_front((inLeft + inRight) / 2);
    } else if (mInputChannel == ChannelLeft) {
        mInputBuffer.push_front(inLeft);
    } else if (mInputChannel == ChannelRight) {
        mInputBuffer.push_front(inRight);
    }
    
    bool swap;
    const boost::container::vector<std::pair<float, float> >& hrtf = mHRTF->getHRTF(getElevation(), getAngle(), swap);
    
    for (int i = 0 ; i < mInputBuffer.size() && i < hrtf.size() ; ++i) {
        // the samples are interleaved (left is every other starting at 0)
        //                             (right is every other starting at 1)
        outLeft += mInputBuffer[i] * (swap ? hrtf[i].second : hrtf[i].first);
        outRight += mInputBuffer[i] * (swap ? hrtf[i].first : hrtf[i].second);
    }
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
