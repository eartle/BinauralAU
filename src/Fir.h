// fir.h
// Michael Coffey 2005
//

#pragma once

#include <boost/container/vector.hpp>
#include <boost/container/deque.hpp>

static const float ParamAngleDefaultValue = 0.0f;
static const float ParamElevationDefaultValue = 0.0f;

class Fir {
public:
	enum Channel {
		ChannelLeft,
		ChannelRight,
		ChannelMix
	};

public:
	Fir(Channel inputChannel);
    ~Fir();

	void putNextInput(const float aInputLeft, const float aInputRight);

    float getOutput(Channel aEar) const;

	float getElevation() const;
	void setElevation(float elevation);
	
	float getAngle() const;
	void setAngle(float angle);

private:
    void readFile(const std::string& fname, boost::container::vector<float>& list);
    
    int getAngleIndex() const;
    int getElevationIndex() const;
    
    int elevationFidelity(int height) const;

private:
    Channel mInputChannel;
	boost::container::deque<float> mPastInputs;

	float mElevation;
	float mAngle;
    
    class HRTF* mHRTF;
};
