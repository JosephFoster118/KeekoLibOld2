

#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include "PeriodicThread.h"
#include "TCPServer.h"
#include "Span.h"
#include "Heap.h"
#include "DynamicLibrary.h"
#include "ThreadPool.h"
using namespace std::chrono_literals;

using std::cout;
using std::endl;



int main()
{


    // void *handle;
    // std::unique_ptr<int>  (*boop)();
    // char *error;

    // handle = dlopen ("./lib/libSharedExample.so", RTLD_NOW);
    // if ((error = dlerror()) != NULL)
    // {
    //     printf("ERROR!\n");
    //     fputs(error, stderr);
    //     exit(1);
    // }
    
    // boop = (std::unique_ptr<int>  (*)(void))dlsym(handle, "foobar");
    // if ((error = dlerror()) != NULL)
    // {
    //     printf("ERROR!\n");
    //     fputs(error, stderr);
    //     exit(1);
    // }make insta

    // cout << *((*boop)()) << endl;
    // dlclose(handle);

    // KeekoLib::DynamicLibrary lib{"./lib/libSharedExample.so", false};
    // int(*boop)();
    // boop = lib.loadFunction<int(*)()>("foobar");
    // cout << boop() << endl;


    KeekoLib::ThreadPool pool{};

    
    return 0;
}
