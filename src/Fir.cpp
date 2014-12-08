
#include <string>
#include <math.h>
#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/range/const_iterator.hpp>

#include <Accelerate/Accelerate.h>

#include "Fir.h"
#include "Utils.h"
#include "Diffuse.h"
#include "HRTFDB.h"

using namespace boost;
using namespace container;

// At 44,100Khz should last about 1.5 seconds before a memcpy
#define INPUT_BUFFER_TOTAL_SIZE 0x10000

Fir::Fir(Channel inputChannel)
    :mInputChannel(inputChannel),
        mInputBuffer(INPUT_BUFFER_TOTAL_SIZE, PAST_INPUT_MAX_SIZE),
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
    const std::pair<vector<float>, vector<float> >& hrtf = mHRTF->getHRTF(getElevation(), getAngle(), swap);

    int n = std::min(mInputBuffer.size(), hrtf.first.size());
    const float* input = mInputBuffer.data();
    
    // multiply two vectors and then add the results together
    vDSP_vmul(hrtf.first.data(), 1, input, 1, mOutputBuffer, 1, n);
    vDSP_sve(mOutputBuffer, 1, swap ? &outRight : &outLeft, n);
    
    vDSP_vmul(hrtf.second.data(), 1, input, 1, mOutputBuffer, 1, n);
    vDSP_sve(mOutputBuffer, 1, swap ? &outLeft : &outRight, n);
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
