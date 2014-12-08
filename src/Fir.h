// fir.h
// Michael Coffey 2005
//

#pragma once

#include "InputBuffer.h"

static const float ParamAngleDefaultValue = 0.0f;
static const float ParamElevationDefaultValue = 0.0f;

#define PAST_INPUT_MAX_SIZE 4096

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
    InputBuffer<float> mInputBuffer;

	float mElevation;
	float mAngle;
    
    class HRTF* mHRTF;

    float mOutputBuffer[PAST_INPUT_MAX_SIZE];
};
