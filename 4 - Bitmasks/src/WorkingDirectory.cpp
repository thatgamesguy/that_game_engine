#include "WorkingDirectory.hpp"

WorkingDirectory::WorkingDirectory()
{
    path = "./resources/";
    
#ifdef MACOS
    
    // Change the default working directory to that of the XCode resource path on MacOS.
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        CFRelease(resourcesURL);
        chdir(path);
    }
    
    //TODO: why would this fail? what should we do if it does? It will result in resources not loading on mac so it is a big deal.
    
#endif
}
