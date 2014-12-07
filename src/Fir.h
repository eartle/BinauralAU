// fir.h
// Michael Coffey 2005
//

#pragma once

#include <boost/container/vector.hpp>

#define LENGTH 128

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
    void read_file(const std::string& fname, boost::container::vector<float>& list, bool left);

private:
	float mPastInputs[LENGTH];
	boost::container::vector<float> mHRTFs[14];

	float mHeight;
	float mAngle;

	Source mSource;
};
