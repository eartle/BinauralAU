// fir.h
// Michael Coffey 2005
//

#pragma once

#include "hrtf.h"

class Fir {
public:
	enum Source	{
		Left = 0,
		Right = 1,
		Both = 2,
	};

	enum Ear {
		LeftEar = 0,
		RightEar = 1,
	};

public:

	Fir();
	~Fir();

	void NextInput(const float aInputLeft, const float aInputRight);

	float LeftOutput() const;
	float RightOutput() const;

	float Height() const;
	void SetHeight(float aHeight);
	
	float Angle() const;
	void SetAngle(float aAngle);

private:
	float Output(Ear aEar) const;

private:
	float mPastInputs[LENGTH];
	const float* mHRTFs[14];

	float mHeight;
	float mAngle;

	Source mSource;
};
