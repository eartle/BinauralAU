// fir.h
// Michael Coffey 2005
//

#pragma once

#include <boost/container/vector.hpp>
#include <boost/circular_buffer.hpp>

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

    void process(float inLeft, float inRight,
                    float& outLeft, float& outRight);

	float getElevation() const;
	void setElevation(float elevation);
	
	float getAngle() const;
	void setAngle(float angle);

private:
    Channel mInputChannel;
	boost::circular_buffer<float> mInputBuffer;

	float mElevation;
	float mAngle;
    
    class HRTF* mHRTF;
};
