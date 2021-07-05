#include <exception>
#include <string>

namespace KeekoLib
{

class DynamicLibraryLoadingFailed : public std::exception {
	std::string file_name;
    
public:
    DynamicLibraryLoadingFailed(std::string file_name_)
    {
        file_name = file_name_;
    }
    
    std::string get_file() const { return file_name; }

    const char * what () const throw ()
    {
    	return "DynamicLibraryLoadingFailed";
    }
       
};

class DynamicLibraryLoadingSymbolFailed : public std::exception {
	std::string symbol_name;
    
public:
    DynamicLibraryLoadingSymbolFailed(std::string symbol_name_)
    {
        symbol_name = symbol_name_;
    }
    
    std::string get_symbol() const { return symbol_name; }

    const char * what () const throw ()
    {
    	return "DynamicLibraryLoadingSymbolFailed";
    }
       
};

}// namespace KeekoLib