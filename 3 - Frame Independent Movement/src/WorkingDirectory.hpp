#ifndef RESOURCE_PATH_HPP
#define RESOURCE_PATH_HPP

#include <string>

#ifdef _MACOS
#include "CoreFoundation/CoreFoundation.h"
#elif _WIN32
#include <windows.h>
#include <Shlwapi.h>
#endif

class WorkingDirectory
{
public:
    WorkingDirectory();
    
    inline const std::string& Get()
    {
        return path;
    }
    
private:
    std::string path;
};

#endif
