#include <sys/ipc.h>
#include <sys/shm.h>
#include <filesystem>
#include <string>


namespace Keeko
{

class SharedMemory
{
public:
    SharedMemory() = delete;
    SharedMemory(const SharedMemory&) = delete;//Removes the copy constructor

    SharedMemory(std::string path);


private:

    std::string path;

};

}// namespace Keeko