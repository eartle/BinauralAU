
#pragma once

#include <AUEffectBase.h>
#include <AUBase.h>

#include "BinauralVersion.h"
#include "Fir.h"

#if AU_DEBUG_DISPATCHER
#include "AUDebugDispatcher.h"
#endif

// parameters
static const float kDefaultValue_ParamOne = 0;
static const float kDefaultValue_ParamTwo = 0;

static CFStringRef kParameterOneName = CFSTR("Angle");
static CFStringRef kParameterTwoName = CFSTR("Height");

enum {
	kParam_One,
	kParam_Two,
	kNumberOfParameters
};

class Binaural : public AUBase {
public:
	Binaural(AudioUnit component);
	~Binaural();
	
	ComponentResult GetParameterValueStrings(AudioUnitScope inScope, AudioUnitParameterID inParameterID, CFArrayRef* outStrings);
	ComponentResult GetParameterInfo(AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo& outParameterInfo);
	ComponentResult GetPropertyInfo(AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, UInt32& outDataSize, Boolean& outWritable);
	ComponentResult GetProperty(AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, void* outData);
	
	bool StreamFormatWritable(AudioUnitScope scope, AudioUnitElement element);
											
	UInt32 SupportedNumChannels(const AUChannelInfo** outInfo);
	
    bool CanScheduleParameters() const;
    
 	bool SupportsTail();

    ComponentResult	Version();
	
	OSStatus ProcessBufferLists(AudioUnitRenderActionFlags& iFlags, const AudioBufferList& inBufferList, AudioBufferList& outBufferList, UInt32 iFrames);
	
private:
	Fir* iFirFilter;
};
