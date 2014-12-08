
#pragma once

#include <AUEffectBase.h>

#include "BinauralVersion.h"
#include "Fir.h"

enum {
	PARAM_ANGLE,
	PARAM_ELEVATION,
	PARAM_COUNT
};

class Binaural : public AUEffectBase {
public:
	Binaural(AudioUnit component);
	~Binaural();
	
	ComponentResult GetParameterInfo(AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo& outParameterInfo);
	
	bool StreamFormatWritable(AudioUnitScope scope, AudioUnitElement element);
											
	UInt32 SupportedNumChannels(const AUChannelInfo** outInfo);

    ComponentResult	Version();
	
	OSStatus ProcessBufferLists(AudioUnitRenderActionFlags& iFlags, const AudioBufferList& inBufferList, AudioBufferList& outBufferList, UInt32 iFrames);
	
private:
	Fir mFirFilter;
};
