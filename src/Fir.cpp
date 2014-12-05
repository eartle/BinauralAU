// fir.cpp
// Michael Coffey
//

#include "fir.h"
#include "hrtf.h"

Fir::Fir()
	{
	iSource = Left;

	iCurrentHeight = 0;
	iNewHeight = 0;
	iCurrentAngle = 0;
	iNewAngle = 0;

	for (int i(0); i < LENGTH ;++i)
		{
		iPastInputs[i] = new float(0);
		}

	iHRTFs[0] = reinterpret_cast<const float*>(ImpResElev_40);
	iHRTFs[1] = reinterpret_cast<const float*>(ImpResElev_30);
	iHRTFs[2] = reinterpret_cast<const float*>(ImpResElev_20);
	iHRTFs[3] = reinterpret_cast<const float*>(ImpResElev_10);
	iHRTFs[4] = reinterpret_cast<const float*>(ImpResElev0);
	iHRTFs[5] = reinterpret_cast<const float*>(ImpResElev10);
	iHRTFs[6] = reinterpret_cast<const float*>(ImpResElev20);
	iHRTFs[7] = reinterpret_cast<const float*>(ImpResElev30);
	iHRTFs[8] = reinterpret_cast<const float*>(ImpResElev40);
	iHRTFs[9] = reinterpret_cast<const float*>(ImpResElev50);
	iHRTFs[10] = reinterpret_cast<const float*>(ImpResElev60);
	iHRTFs[11] = reinterpret_cast<const float*>(ImpResElev70);
	iHRTFs[12] = reinterpret_cast<const float*>(ImpResElev80);
	iHRTFs[13] = reinterpret_cast<const float*>(ImpResElev90);
	}

Fir::~Fir()
	{
	for (int i(0); i < LENGTH ;++i)
		{
		delete iPastInputs[i];
		}
	}

float Fir::LeftOutput() const
	{
	return Output(LeftEar);
	}

float Fir::RightOutput() const
	{
	return Output(RightEar);
	}

float Fir::Output(Ear aEar) const
	{
	int impulseResponse(0);
	int height(static_cast<int>(iCurrentHeight * 13));
	int precision(1);
	float coeff(1);

	if		((height >= 2)&&(height <= 6))	precision = 37;
	else if	((height == 1)||(height == 7))	precision = 31;
	else if	((height == 0)||(height == 8))	precision = 29;
	else if	(height == 9)					precision = 23;
	else if	(height == 10)					precision = 19;
	else if	(height == 11)					precision = 13;
	else if	(height == 12)					precision = 7;
	else if	(height == 13)					precision = 1;

	if (iCurrentAngle < 0.5)
		{
		float angle((iCurrentAngle * 2) * (static_cast<float>(precision) - 1));
		impulseResponse = static_cast<int>(angle);
		coeff = angle - impulseResponse;
		}
	else
		{
		float angle(static_cast<float>((static_cast<float>(precision) - 1) - (((iCurrentAngle - 0.5) * 2) * (static_cast<float>(precision) - 1))));
		impulseResponse = static_cast<int>(angle);
		coeff = angle - impulseResponse;

		if (aEar == LeftEar) aEar = RightEar;
		else if (aEar == RightEar) aEar = LeftEar;
		}

	float output(0);
	for (int i(0); i < LENGTH; ++i)
		{
		output += *(iPastInputs[i])
			* ((1-coeff) * iHRTFs[height][(aEar *  precision * LENGTH) + (LENGTH * impulseResponse) + i]
			+  ( coeff ) * iHRTFs[height][(aEar *  precision * LENGTH) + (LENGTH * impulseResponse) + i]);
		}

	return output;
	}

void Fir::NextInput(const float aInputLeft, const float aInputRight)
	{
	MoveAngle();
	MoveHeight();

	float* temp = iPastInputs[LENGTH-1];

	switch (iSource)
		{
		case Both:
			{
			*temp = (aInputLeft + aInputRight) / 2;
			break;
			}
		case Left:
			{
			*temp = aInputLeft;
			break;
			}
		case Right:
			{
			*temp = aInputRight;
			break;
			}
		default:
			break;
		}
	for (int i(LENGTH-1); i > 0; --i)
		{
		iPastInputs[i] = iPastInputs[i-1];
		}
	iPastInputs[0] = temp;
	}

float Fir::Height() const
	{
	return iNewHeight;
	}
float Fir::Angle() const
	{
	return iNewAngle;
	}

void Fir::SetHeight(float aHeight)
	{
	iNewHeight = aHeight;
	}
void Fir::SetAngle(float aAngle)
	{
	iNewAngle = aAngle;
	}

void Fir::MoveAngle()
	{
	if (iCurrentAngle > iNewAngle)
		{
		iCurrentAngle -= static_cast<float>(0.000075);
		}
	else if (iCurrentAngle < iNewAngle)
		{
		iCurrentAngle += static_cast<float>(0.000075);
		}
	}

void Fir::MoveHeight()
	{
	iCurrentHeight = iNewHeight;
	}