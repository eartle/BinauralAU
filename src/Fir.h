// fir.h
// Michael Coffey 2005
//

#pragma once

#include <boost/container/vector.hpp>

#define LENGTH 128
static const float ParamAngleDefaultValue = 0.0f;
static const float ParamElevationDefaultValue = 0.3f;

class Fir {
public:
	enum Channel {
		ChannelLeft,
		ChannelRight,
		ChannelMix
	};

public:
	Fir();
	~Fir();

	void putNextInput(const float aInputLeft, const float aInputRight);

    float getOutput(Channel aEar) const;

	float getElevation() const;
	void setElevation(float elevation);
	
	float getAngle() const;
	void setAngle(float angle);

private:
    void readFile(const std::string& fname, boost::container::vector<float>& list, bool left);

private:
	float mPastInputs[LENGTH];
	boost::container::vector<float> mHRTFs[14];

	float mElevation;
	float mAngle;

	Channel mInputChannel;
};
