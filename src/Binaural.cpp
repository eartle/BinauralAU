#include "Binaural.h"

AUDIOCOMPONENT_ENTRY(AUBaseProcessFactory, Binaural)

Binaural::Binaural(AudioUnit component)
    :AUEffectBase(component)
{
    CreateElements();
    Globals()->UseIndexedParameters(PARAM_COUNT);
    SetParameter(PARAM_ANGLE, kAudioUnitScope_Global, 0, ParamAngleDefaultValue, 0);
    SetParameter(PARAM_HEIGHT, kAudioUnitScope_Global, 0, ParamHeightDefaultValue, 0);
        
#if AU_DEBUG_DISPATCHER
    mDebugDispatcher = new AUDebugDispatcher(this);
#endif
}

Binaural::~Binaural () {
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
            case PARAM_ANGLE:
                AUBase::FillInParameterName (outParameterInfo, ParamAngleName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_LinearGain;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 1;
                outParameterInfo.defaultValue = ParamAngleDefaultValue;
                break;
            case PARAM_HEIGHT:
                AUBase::FillInParameterName (outParameterInfo, ParamHeightName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_LinearGain;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 1;
                outParameterInfo.defaultValue = ParamHeightDefaultValue;
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
    return AUEffectBase::GetPropertyInfo(inID, inScope, inElement, outDataSize, outWritable);
}

ComponentResult Binaural::GetProperty(AudioUnitPropertyID inID, AudioUnitScope inScope, AudioUnitElement inElement, void* outData) {
    return AUEffectBase::GetProperty(inID, inScope, inElement, outData);
}

UInt32 Binaural::SupportedNumChannels(const AUChannelInfo** outInfo)
{   
    // set an array of arrays of different combinations of supported numbers of ins and outs
    static const AUChannelInfo sChannels[1] = {{ -1, 2}};   
    if (outInfo)
        *outInfo = sChannels;
    return sizeof(sChannels) / sizeof(AUChannelInfo);
}

OSStatus Binaural::ProcessBufferLists(AudioUnitRenderActionFlags& ioActionFlags,
                                        const AudioBufferList& inBuffer,
                                        AudioBufferList& outBuffer,
                                        UInt32 inFrames) {
    mFirFilter.SetAngle(Globals()->GetParameter(PARAM_ANGLE));
    mFirFilter.SetHeight(Globals()->GetParameter(PARAM_HEIGHT));
    
    const float* srcBuffer = (Float32 *)inBuffer.mBuffers[0].mData;
    
    float* destBufferL = (Float32 *)outBuffer.mBuffers[0].mData;
    float* destBufferR = (Float32 *)outBuffer.mBuffers[1].mData;
    
    for (int i = 0 ; i < inFrames ; ++i) {
        // we are always using the first input channel no matter how many there are
        mFirFilter.NextInput(*(srcBuffer + i), *(srcBuffer + i));
        
        // here's where you do your DSP work
        *(destBufferL + i) = mFirFilter.LeftOutput();
        *(destBufferR + i) = mFirFilter.RightOutput();
    }
    
    return noErr; 
}
