
#pragma once

#include <string>

#include <boost/filesystem/fstream.hpp>

class Utils {
private:
    Utils();
public:
    static std::string getResourcePath();
    
    static boost::filesystem::fstream& getLogger();

private:
    static boost::filesystem::fstream* mLog;
};
