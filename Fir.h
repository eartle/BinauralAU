// fir.h
// Michael Coffey 2005
//

#ifndef _FIR_
#define _FIR_

#include "hrtf.h"

class Fir
	{
public:

	enum Source
		{
		Left = 0,
		Right = 1,
		Both = 2,
		};

	enum Ear 
		{
		LeftEar = 0,
		RightEar = 1,
		};

	Fir();
	~Fir();

	void NextInput(const float aInputLeft, const float aInputRight);

	float LeftOutput() const;
	float RightOutput() const;

	float Height() const;
	void SetHeight(float aHeight);
	
	float Angle() const;
	void SetAngle(float aAngle);


private:
	float Output(Ear aEar) const;

	void MoveAngle();
	void MoveHeight();

private:
	float* iPastInputs[LENGTH];
	const float* iHRTFs[14];

	float iCurrentHeight;
	float iNewHeight;

	float iCurrentAngle;
	float iNewAngle;

	Source iSource;
public:
	};

#endif // _FIR_