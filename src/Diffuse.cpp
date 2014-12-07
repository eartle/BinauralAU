
#include <string>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>

#include "Diffuse.h"
#include "Utils.h"

Diffuse::Diffuse() {
    std::string path = Utils::getResourcePath() + "/diffuse";
    Utils::getLogger() << path << std::endl;
    std::string filename_format = "/H%de%03da.wav";
    
    for (int elev_index = 0 ; elev_index < 14 ; ++elev_index) {
        int elevation = (elev_index - 4) * 10;
        
        for (int angle = 0 ; angle <= 180 ; ++angle) {
            // try finding a file for every angle
            std::string filename = path + (boost::format(filename_format) % elevation % angle).str();
            if (boost::filesystem::exists(filename)) {
                boost::container::vector<float> angle_samples;
                readFile(filename, angle_samples);
                mHRTFs[elev_index].push_back(angle_samples);
            }
        }
        
        Utils::getLogger() << boost::format("elev: %1% size: %2%.") % elev_index % mHRTFs[elev_index].size() << std::endl;
    }
}

const boost::container::vector<float>& Diffuse::getHRTF(float elevation, float angle, bool& swap) const {
    swap = angle > 180.0f;
    return mHRTFs[getElevationIndex(elevation)][getAngleIndex(elevation, angle)];
}

int Diffuse::getElevationIndex(float elevation) const {
    // elevation goes from -40º to 90º
    //                      0   to 13
    return boost::math::round((elevation + 40.0f) / 10.0f);
}

int Diffuse::getAngleIndex(float elevation, float angle) const {
    // getAngle() goes from 0º to 360º
    float adjusted_angle = (angle > 180.0f) ? 360.0f - angle : angle;
    // adjusted_angle goes from 0º to 180º to 0º
    //                 0  to elevationFidelity(int elevation)
    return boost::math::round((mHRTFs[getElevationIndex(elevation)].size() - 1) * (adjusted_angle / 180.0f));
}