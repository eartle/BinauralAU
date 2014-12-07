
#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>

#include <sndfile.hh>

#include "Fir.h"

int elevationFidelity(int height) {
    if ((height >= 2)&&(height <= 6))
        return 37;
    else if	((height == 1)||(height == 7))
        return 31;
    else if	((height == 0)||(height == 8))
        return 29;
    else if	(height == 9)
        return 23;
    else if	(height == 10)
        return 19;
    else if	(height == 11)
        return 13;
    else if	(height == 12)
        return 7;
    else if	(height == 13)
        return 1;
    
    return 0;
}

void Fir::read_file(const std::string& fname, boost::container::vector<float>& list, bool left) {
    SndfileHandle file(fname);
    sf_count_t count = file.channels() * file.frames();
    //mLog << fname << ": " << file.frames() << std::endl;
    float* buffer = new float[count];
    sf_count_t actual_count = file.read(buffer, count);
    for (int i = left ? 0 : 1 ; i < actual_count ; i += 2) {
        list.push_back(buffer[i]);
    }
    delete[] buffer;
}

Fir::Fir()
    :mLog("/Users/coffey/Library/Logs/binaural.log", std::ios_base::trunc|std::ios_base::out),
        mHeight(0),
        mAngle(0),
        mSource(Left)
{
    //std::string path = (boost::filesystem::current_path()).string() + "/../Resources/";
    std::string path = "/Users/coffey/Library/Audio/Plug-Ins/Components/binaural.component/Contents/Resources/";
    
    std::string filename_format = "H%de%03da.wav";
    
    for (int elev_i = 0 ; elev_i < 14 ; ++elev_i) {
        int elev = (elev_i - 4) * 10;
        
        //mLog << "elevation left: " << elev << std::endl;
        
        for (int angle = 0 ; angle <= 180 ; ++angle) {
            std::string filename = path + (boost::format(filename_format) % elev % angle).str();
            if (boost::filesystem::exists(filename))
                read_file(filename, mHRTFs[elev_i], true);
        }
        
        //mLog << "elevation right: " << elev << std::endl;
        
        for (int angle = 0 ; angle <= 180 ; ++angle) {
            std::string filename = path + (boost::format(filename_format) % elev % angle).str();
            if (boost::filesystem::exists(filename))
                read_file(filename, mHRTFs[elev_i], false);
        }
    }
}

Fir::~Fir() {}

float Fir::LeftOutput() const {
    return Output(LeftEar);
}

float Fir::RightOutput() const {
	return Output(RightEar);
}

float Fir::Output(Ear aEar) const {
	int impulseResponse = 0;
    int height = static_cast<int>(boost::math::round(mHeight * 13));
	int fidelity = elevationFidelity(height);
	float coeff = 1;

	if (mAngle < 0.5) {
		float angle((mAngle * 2) * (static_cast<float>(fidelity) - 1));
		impulseResponse = static_cast<int>(boost::math::round(angle));
		coeff = angle - impulseResponse;
	} else {
		float angle(static_cast<float>((static_cast<float>(fidelity) - 1) - (((mAngle - 0.5) * 2) * (static_cast<float>(fidelity) - 1))));
		impulseResponse = static_cast<int>(boost::math::round(angle));
		coeff = angle - impulseResponse;

		if (aEar == LeftEar)
            aEar = RightEar;
		else if (aEar == RightEar)
            aEar = LeftEar;
	}

	float output = 0;
    
	for (int i(0); i < LENGTH; ++i)	{
		output += mPastInputs[i]
			* ((1-coeff) * mHRTFs[height][(aEar *  fidelity * LENGTH) + (LENGTH * impulseResponse) + i]
			+  ( coeff ) * mHRTFs[height][(aEar *  fidelity * LENGTH) + (LENGTH * impulseResponse) + i]);
	}

	return output;
}

void Fir::NextInput(const float aInputLeft, const float aInputRight) {
	for (int i(LENGTH-1); i > 0; --i){
		mPastInputs[i] = mPastInputs[i-1];
	}
    
    if (mSource == Both) {
        mPastInputs[0] = (aInputLeft + aInputRight) / 2;
    } else if (mSource == Left) {
        mPastInputs[0] = aInputLeft;
    } else if (mSource == Right) {
        mPastInputs[0] = aInputRight;
    }
}

float Fir::Height() const {
	return mHeight;
}

float Fir::Angle() const {
	return mAngle;
}

void Fir::SetHeight(float height) {
	mHeight = height;
}

void Fir::SetAngle(float angle) {
	mAngle = angle;
}
