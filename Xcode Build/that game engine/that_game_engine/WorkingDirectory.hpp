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
    
    inline std::string Get()
    {
        if(path.length() > 0)
        {
            return path;
        }

        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd)) != nullptr)
        {
            path = std::string(cwd) + std::string("/");
        }
        

        return path;
    }
    
private:
    std::string path;
};

#endif
