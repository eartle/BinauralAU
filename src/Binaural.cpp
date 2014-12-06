#include "Binaural.h"

AUDIOCOMPONENT_ENTRY(AUBaseFactory, Binaural)

Binaural::Binaural(AudioUnit component)
	: AUBase(component, 1, 1)
{
	CreateElements();
	Globals()->UseIndexedParameters(kNumberOfParameters);
	SetParameter(kParam_One, kAudioUnitScope_Global, 0, kDefaultValue_ParamOne, 0);
	SetParameter(kParam_Two, kAudioUnitScope_Global, 0, kDefaultValue_ParamTwo, 0);
	
	iFirFilter = new Fir();
        
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher (this);
#endif
}

Binaural::~Binaural () {
    delete iFirFilter;
#if AU_DEBUG_DISPATCHER
   delete mDebugDispatcher; 
#endif
}

ComponentResult Binaural::Version() {
    return kBinauralVersion;
}

bool Binaural::SupportsTail() {
    return false;
}

bool Binaural::CanScheduleParameters() const {
    return false;
}

bool Binaural::StreamFormatWritable(AudioUnitScope scope, AudioUnitElement element) {
	return IsInitialized() ? false : true;
}

ComponentResult Binaural::GetParameterValueStrings(AudioUnitScope inScope, AudioUnitParameterID inParameterID, CFArrayRef* outStrings) {  
    return kAudioUnitErr_InvalidProperty;
}

ComponentResult Binaural::GetParameterInfo(AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo &outParameterInfo) {
	ComponentResult result = noErr;

	outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable | kAudioUnitParameterFlag_IsReadable;
    
    if (inScope == kAudioUnitScope_Global) {
        switch(inParameterID)
        {
            case kParam_One:
                AUBase::FillInParameterName (outParameterInfo, kParameterOneName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_LinearGain;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 1;
                outParameterInfo.defaultValue = kDefaultValue_ParamOne;
                break;
			case kParam_Two:
                AUBase::FillInParameterName (outParameterInfo, kParameterTwoName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_LinearGain;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 1;
                outParameterInfo.defaultValue = kDefaultValue_ParamOne;
                break;
            default:
                result = kAudioUnitErr_InvalidParameter;
                break;
            }
	} else {
        result = kAudioUnitErr_InvalidParameter;
    }

	return result;
}

ComponentResult Binaural::GetPropertyInfo(AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, UInt32& outDataSize, Boolean& outWritable) {
	return AUBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

ComponentResult Binaural::GetProperty(AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, void* outData) {
	return AUBase::GetProperty (inID, inScope, inElement, outData);
}

UInt32 Binaural::SupportedNumChannels(const AUChannelInfo** outInfo)
{	
	// set an array of arrays of different combinations of supported numbers 
	// of ins and outs
	static const AUChannelInfo sChannels[1] = {{ -1, 2}};	
	if (outInfo) *outInfo = sChannels;
	return sizeof (sChannels) / sizeof (AUChannelInfo);
}

OSStatus Binaural::ProcessBufferLists(AudioUnitRenderActionFlags& iFlags, const AudioBufferList& inBufferList, AudioBufferList& outBufferList, UInt32 iFrames) {
	iFirFilter->SetAngle(Globals()->GetParameter( kParam_One ));
	iFirFilter->SetHeight(Globals()->GetParameter( kParam_Two ));
	
	float input = *static_cast<float*>(inBufferList.mBuffers[0].mData);
	
	// we are always using the first input channel no matter how many there are
	iFirFilter->NextInput(input, input);

	// here's where you do your DSP work
	static float left = iFirFilter->LeftOutput();
	outBufferList.mBuffers[0].mData = &left;
	float right = iFirFilter->RightOutput();
	outBufferList.mBuffers[1].mData = &right;
	
	return noErr; 
}
