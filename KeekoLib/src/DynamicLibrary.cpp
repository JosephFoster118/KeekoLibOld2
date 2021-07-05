#include "DynamicLibrary.h"

namespace KeekoLib
{

DynamicLibrary::DynamicLibrary(std::string file_name, bool lazy)
{
    char *error;
    handle = dlopen (file_name.c_str(), ((lazy) ? RTLD_LAZY:RTLD_NOW));
    if ((error = dlerror()) != NULL)
    {
        throw DynamicLibraryLoadingFailed{file_name};
    }
}

DynamicLibrary::~DynamicLibrary()
{
    if(handle != nullptr)
    {
        dlclose(handle);
    }
}

}// namespace KeekoLib
