#pragma once

#include "Core/Common/Public/RingQueue.h"
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <functional>
#include <future>

namespace Lumen::Core
{
    // Parallel task processing without dependence
    class ThreadPool
    {
    public:
        ThreadPool(unsigned int num);
        ~ThreadPool();

        template<typename F, typename... Args>
        decltype(auto) Enqueue(F&& callable, Args&&... args);

    private:
        std::vector<std::thread> mThreads;
        RingQueue<std::function<void()>> mTasks;
        std::mutex mMutex;
        std::condition_variable mCondition;
        bool bExit = false;
    };

    template<typename F, typename... Args>
    decltype(auto) ThreadPool::Enqueue(F&& callable, Args&&... args)
    {
        using ReturnType = std::invoke_result_t<F, Args...>;
        auto task = std::make_shared< std::packaged_task<ReturnType()> >(
            std::bind(std::forward<F>(callable), std::forward<Args>(args)...)
            );
        std::future<ReturnType> taskFuture = task->get_future();
        {
            std::unique_lock<std::mutex> lock(mMutex);
            mTasks.Emplace([task]() {(*task)(); });
        }
        mCondition.notify_one();
        return taskFuture;
    }
}