#pragma once

#include <string>
#include <dlfcn.h>

#include "DynamicLibraryExceptions.h"

namespace KeekoLib
{

class DynamicLibrary
{
public:
    DynamicLibrary(std::string file_name, bool lazy = true);
    DynamicLibrary() = delete;//Removes the default constructor
    DynamicLibrary(const DynamicLibrary&) = delete;//Removes the copy constructor
    virtual ~DynamicLibrary();

    template<class T>
    T loadFunction(std::string symbol)
    {
        auto result = dlsym(handle,symbol.c_str());
        if(dlerror() != NULL)
        {
            throw DynamicLibraryLoadingSymbolFailed{symbol};
        }
        return reinterpret_cast<T>(result);
    }
    
protected:
    void *handle{nullptr};
};

}// namespace KeekoLib
