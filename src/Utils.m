
#include "Utils.h"

#include <Foundation/Foundation.h>

boost::filesystem::fstream* Utils::mLog = NULL;

std::string Utils::getResourcePath() {
    return [[[NSBundle bundleWithIdentifier:@"com.coffey.audiounit.Binaural"] resourcePath] UTF8String];
}

boost::filesystem::fstream& Utils::getLogger() {
    if (mLog == NULL) {
        std::string home = [NSHomeDirectory() UTF8String];
        mLog = new boost::filesystem::fstream(
                        home + "/Library/Logs/binaural.log",
                        std::ios_base::trunc|std::ios_base::out);
    }
    
    return *mLog;
}