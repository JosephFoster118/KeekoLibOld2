#include "ThreadPool.h"


namespace KeekoLib
{

ThreadPool::ThreadPool(uint32_t size): threads{size}
{
    for(uint32_t i = 0; i < threads.size(); i++)
    {
        printf("Boop\n");
        threads[i].thread = std::unique_ptr<std::thread>{new std::thread{baseThreadLambda, std::ref(threads[i])}};
    }
}

ThreadPool::ThreadPool():  ThreadPool(10)
{
    //Nothing
}

ThreadPool::~ThreadPool()
{
    const std::lock_guard<std::mutex> lock(mtx);
    for(uint32_t i = 0; i < threads.size(); i++)
    {
        if(threads[i].thread->joinable())
        {
            threads[i].run_cv.notify_all();
            threads[i].thread->join();
            printf("Killed thread %s\n", threads[i].name.c_str());
        }
    }
}

}// namespace KeekoLib
