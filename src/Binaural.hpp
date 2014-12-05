// binaural.hpp
// Michael Coffey
//

#ifndef _BINAURAL_
#define _BINAURAL_

#include <audioeffectx.h>

#include "fir.h"

class Binaural : public AudioEffectX
	{
public:
	Binaural(audioMasterCallback audioMaster);
	~Binaural();

	// Processes
	virtual void process(float** inputs, float** outputs, long sampleFrames);
	virtual void processReplacing(float** inputs, float** outputs, long sampleFrames);

	// Program
	virtual void setProgramName(char* name);
	virtual void getProgramName(char* name);

	// Parameters
	virtual void setParameter(long index, float value);
	virtual float getParameter(long index);
	virtual void getParameterLabel(long index, char* label);
	virtual void getParameterDisplay(long index, char* text);
	virtual void getParameterName(long index, char* text);

	virtual bool getEffectName(char* name);
	virtual bool getVendorString(char* text);
	virtual bool getProductString(char* text);
	virtual long getVendorVersion() { return 1000; }
	
	virtual VstPlugCategory getPlugCategory() { return kPlugCategEffect; }

protected:
	Fir iFir;
	char iProgramName[32];
	};

#endif // _BINAURAL_
