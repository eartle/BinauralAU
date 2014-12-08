#include "Binaural.h"

#if AU_DEBUG_DISPATCHER
#include "AUDebugDispatcher.h"
#endif

// parameters
static CFStringRef ParamAngleName = CFSTR("Angle");
static CFStringRef ParamElevationName = CFSTR("Elevation");

AUDIOCOMPONENT_ENTRY(AUBaseProcessFactory, Binaural)

Binaural::Binaural(AudioUnit component)
    :AUEffectBase(component),
        mFirFilter(Fir::ChannelMix)
{
    CreateElements();
    Globals()->UseIndexedParameters(PARAM_COUNT);
    SetParameter(PARAM_ANGLE, ParamAngleDefaultValue);
    SetParameter(PARAM_ELEVATION, ParamElevationDefaultValue);
        
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

bool Binaural::StreamFormatWritable(AudioUnitScope scope, AudioUnitElement element) {
    return IsInitialized() ? false : true;
}

ComponentResult Binaural::GetParameterInfo(AudioUnitScope inScope, AudioUnitParameterID inParameterID, AudioUnitParameterInfo &outParameterInfo) {
    ComponentResult result = noErr;

    outParameterInfo.flags = kAudioUnitParameterFlag_IsWritable | kAudioUnitParameterFlag_IsReadable;
    
    if (inScope == kAudioUnitScope_Global) {
        switch(inParameterID)
        {
            case PARAM_ANGLE:
                AUBase::FillInParameterName (outParameterInfo, ParamAngleName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Degrees;
                outParameterInfo.minValue = 0;
                outParameterInfo.maxValue = 360;
                outParameterInfo.defaultValue = ParamAngleDefaultValue;
                break;
            case PARAM_ELEVATION:
                AUBase::FillInParameterName (outParameterInfo, ParamElevationName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Degrees;
                outParameterInfo.minValue = -40;
                outParameterInfo.maxValue = 90;
                outParameterInfo.defaultValue = ParamElevationDefaultValue;
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

UInt32 Binaural::SupportedNumChannels(const AUChannelInfo** outInfo) {
    // set an array of arrays of different combinations of supported numbers of ins and outs
    static const AUChannelInfo sChannels[] = {{1, 2}, {2, 2}};
    if (outInfo)
        *outInfo = sChannels;
    return sizeof(sChannels) / sizeof(AUChannelInfo);
}

OSStatus Binaural::ProcessBufferLists(AudioUnitRenderActionFlags& inActionFlags,
                                        const AudioBufferList& inBuffer,
                                        AudioBufferList& outBuffer,
                                        UInt32 inFrames) {
    mFirFilter.setAngle(GetParameter(PARAM_ANGLE));
    mFirFilter.setElevation(GetParameter(PARAM_ELEVATION));
    
    const Float32* srcBufferL = (Float32 *)inBuffer.mBuffers[0].mData;
    const Float32* srcBufferR = (Float32 *)inBuffer.mBuffers[(GetNumberOfChannels() == 1) ? 0 : 1].mData;
    
    Float32* destBufferL = (Float32 *)outBuffer.mBuffers[0].mData;
    Float32* destBufferR = (Float32 *)outBuffer.mBuffers[1].mData;
    
    for (int i = 0 ; i < inFrames ; ++i) {
        mFirFilter.process(*(srcBufferL++), *(srcBufferR++),
                           *(destBufferL++), *(destBufferR++));

    }
    
    return noErr; 
}
