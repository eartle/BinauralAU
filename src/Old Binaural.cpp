// binaural.cpp
// Michael Coffey
//

#include <stdio.h>

#include "binaural.hpp"

Binaural::Binaural(audioMasterCallback audioMaster)
	: AudioEffectX(audioMaster, 1, 2)	// 1 program, 2 parameters
	{
	setNumInputs(2);		// stereo in
	setNumOutputs(2);		// stereo out
	setUniqueID('Bina');	// identify
	canMono();				// makes sense to feed both inputs with the same signal
	canProcessReplacing();	// supports both accumulating and replacing output
	strcpy(iProgramName, "Default");	// default program name
	}

Binaural::~Binaural()
	{
	}

void Binaural::setProgramName(char* aName)
	{
	strcpy(iProgramName, aName);
	}

void Binaural::getProgramName(char* aName)
	{
	strcpy(aName, iProgramName);
	}

void Binaural::setParameter(long aIndex, float aValue)
	{
	switch (aIndex)
		{
		case 0:
			iFir.SetHeight(aValue);
			break;
		case 1:
			iFir.SetAngle(aValue);
			break;
		default:
			break;
		}
	}

float Binaural::getParameter(long aIndex)
	{
	float result(0);

	switch (aIndex)
		{
		case 0:
			result = iFir.Height();
			break;
		case 1:
			result = iFir.Angle();
			break;
		default:
			break;
		}
	return result;
	}

void Binaural::getParameterName(long aIndex, char* aLabel)
	{
	switch (aIndex)
		{
		case 0:
			strcpy(aLabel, "Height");
			break;
		case 1:
			strcpy(aLabel, "Angle");
			break;
		default:
			break;
		}
	}

void Binaural::getParameterDisplay(long aIndex, char* aText)
	{
	switch (aIndex)
		{
		case 0:
			{
			int height((int)((iFir.Height() * 130) - 40));
			sprintf(aText, "%d", height);
			break;
			}
		case 1:
			{
			int angle((int)(iFir.Angle() * 360));
			sprintf(aText, "%d", angle);
			break;
			}
		default:
			{
			break;
			}
		}
	}

void Binaural::getParameterLabel(long aIndex, char* aLabel)
	{
	switch (aIndex)
		{
		case 0:
			strcpy(aLabel, "Deg");
			break;
		case 1:
			strcpy(aLabel, "Deg");
			break;
		default:
			break;
		}
	}

bool Binaural::getEffectName(char* aName)
	{
	strcpy(aName, "Binaural");
	return true;
	}

bool Binaural::getProductString(char* aText)
	{
	strcpy(aText, "Binaural");
	return true;
	}

bool Binaural::getVendorString(char* aText)
	{
	strcpy(aText, "Coffey");
	return true;
	}

void Binaural::process(float** aInputs, float** aOutputs, long aSampleFrames)
	{
    float* in1  =  aInputs[0];
    float* in2  =  aInputs[1];
    float* out1 = aOutputs[0];
    float* out2 = aOutputs[1];

	while (--aSampleFrames >= 0)
		{
		iFir.NextInput(*in1++, *in2++);
        (*out1++) += iFir.LeftOutput();	// accumulating
        (*out2++) += iFir.RightOutput();
		}
	}

void Binaural::processReplacing(float** aInputs, float** aOutputs, long aSampleFrames)
	{
    float* in1  =  aInputs[0];
    float* in2  =  aInputs[1];
    float* out1 = aOutputs[0];
    float* out2 = aOutputs[1];

	while (--aSampleFrames >= 0)
		{
		iFir.NextInput(*in1++, *in2++);
        (*out1++) = iFir.LeftOutput();    // replacing
        (*out2++) = iFir.RightOutput();
		}
	}
