#include "Fir.h"
#include "hrtf.h"

Fir::Fir()
    :mSource(Left), mHeight(0), mAngle(0)
{
	mHRTFs[0] = reinterpret_cast<const float*>(ImpResElev_40);
	mHRTFs[1] = reinterpret_cast<const float*>(ImpResElev_30);
	mHRTFs[2] = reinterpret_cast<const float*>(ImpResElev_20);
	mHRTFs[3] = reinterpret_cast<const float*>(ImpResElev_10);
	mHRTFs[4] = reinterpret_cast<const float*>(ImpResElev0);
	mHRTFs[5] = reinterpret_cast<const float*>(ImpResElev10);
	mHRTFs[6] = reinterpret_cast<const float*>(ImpResElev20);
	mHRTFs[7] = reinterpret_cast<const float*>(ImpResElev30);
	mHRTFs[8] = reinterpret_cast<const float*>(ImpResElev40);
	mHRTFs[9] = reinterpret_cast<const float*>(ImpResElev50);
	mHRTFs[10] = reinterpret_cast<const float*>(ImpResElev60);
	mHRTFs[11] = reinterpret_cast<const float*>(ImpResElev70);
	mHRTFs[12] = reinterpret_cast<const float*>(ImpResElev80);
	mHRTFs[13] = reinterpret_cast<const float*>(ImpResElev90);
}

Fir::~Fir() {}

float Fir::LeftOutput() const {
    return Output(LeftEar);
}

float Fir::RightOutput() const {
	return Output(RightEar);
}

float Fir::Output(Ear aEar) const {
	int impulseResponse = 0;
	int height = static_cast<int>(mHeight * 13);
	int precision = 1;
	float coeff = 1;

	if		((height >= 2)&&(height <= 6))	precision = 37;
	else if	((height == 1)||(height == 7))	precision = 31;
	else if	((height == 0)||(height == 8))	precision = 29;
	else if	(height == 9)					precision = 23;
	else if	(height == 10)					precision = 19;
	else if	(height == 11)					precision = 13;
	else if	(height == 12)					precision = 7;
	else if	(height == 13)					precision = 1;

	if (mAngle < 0.5) {
		float angle((mAngle * 2) * (static_cast<float>(precision) - 1));
		impulseResponse = static_cast<int>(angle);
		coeff = angle - impulseResponse;
	} else {
		float angle(static_cast<float>((static_cast<float>(precision) - 1) - (((mAngle - 0.5) * 2) * (static_cast<float>(precision) - 1))));
		impulseResponse = static_cast<int>(angle);
		coeff = angle - impulseResponse;

		if (aEar == LeftEar) aEar = RightEar;
		else if (aEar == RightEar) aEar = LeftEar;
	}

	float output = 0;
	for (int i(0); i < LENGTH; ++i)	{
		output += mPastInputs[i]
			* ((1-coeff) * mHRTFs[height][(aEar *  precision * LENGTH) + (LENGTH * impulseResponse) + i]
			+  ( coeff ) * mHRTFs[height][(aEar *  precision * LENGTH) + (LENGTH * impulseResponse) + i]);
	}

	return output;
}

void Fir::NextInput(const float aInputLeft, const float aInputRight) {
	for (int i(LENGTH-1); i > 0; --i){
		mPastInputs[i] = mPastInputs[i-1];
	}
    
    if (mSource == Both) {
        mPastInputs[0] = (aInputLeft + aInputRight) / 2;
    } else if (mSource == Left) {
        mPastInputs[0] = aInputLeft;
    } else if (mSource == Right) {
        mPastInputs[0] = aInputRight;
    }
}

float Fir::Height() const {
	return mHeight;
}

float Fir::Angle() const {
	return mAngle;
}

void Fir::SetHeight(float height) {
	mHeight = height;
}

void Fir::SetAngle(float angle) {
	mAngle = angle;
}
