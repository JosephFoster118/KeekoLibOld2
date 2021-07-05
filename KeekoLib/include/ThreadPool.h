#pragma once

#include <string>
#include <cstdint>
#include <chrono>
#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <vector>
#include <map>

namespace KeekoLib
{

class ThreadPool
{
public:
    ThreadPool(uint32_t size);
    ThreadPool();//Removes the default constructor
    ThreadPool(const ThreadPool&) = delete;//Removes the copy constructor
    virtual ~ThreadPool();

protected:

    struct ThreadContext
    {
        std::condition_variable run_cv;
        std::unique_ptr<std::thread> thread;
        std::mutex mtx;
        std::string name{"Not Active"};
        bool running{false};
    };

    const std::function<void(ThreadContext&)> baseThreadLambda = [this](ThreadContext &context)
    {
        std::unique_lock<std::mutex> lck{context.mtx};
        if(!shutdown.load())
        {
            context.run_cv.wait(lck);
        }
        if(shutdown.load())
        {
            return;//Shutdown
        }

    };

    std::mutex mtx;
    std::vector<ThreadContext> threads;
    std::map<std::string, uint32_t> name_index;
    std::atomic<bool> shutdown{false};


};

}// namespace KeekoLib


