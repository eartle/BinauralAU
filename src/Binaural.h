
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
	
	ComponentResult GetParameterValueStrings(AudioUnitScope inScope, AudioUnitParameterID inParameterID, CFArrayRef* outStrings);
	ComponentResult GetParameterInfo(AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo& outParameterInfo);
	ComponentResult GetPropertyInfo(AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, UInt32& outDataSize, Boolean& outWritable);
	ComponentResult GetProperty(AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, void* outData);
	
	bool StreamFormatWritable(AudioUnitScope scope, AudioUnitElement element);
											
	UInt32 SupportedNumChannels(const AUChannelInfo** outInfo);
    
 	bool SupportsTail();

    ComponentResult	Version();
	
	OSStatus ProcessBufferLists(AudioUnitRenderActionFlags& iFlags, const AudioBufferList& inBufferList, AudioBufferList& outBufferList, UInt32 iFrames);
	
private:
	Fir mFirFilter;
};
