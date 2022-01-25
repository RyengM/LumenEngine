#pragma once

#include "Task.h"
#include "Core/Common/Public/RingQueue.h"
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <functional>
#include <future>

namespace Lumen::Core
{
    enum class TaskPriority
    {
        High,
        Low
    };

    // Thread pool used for task graph
    class TaskThreadPool
    {
    public:
        TaskThreadPool(unsigned int num);
        ~TaskThreadPool();

        void Enqueue(TaskNodeBase* node, TaskPriority priority = TaskPriority::Low);

    private:
        std::vector<std::thread> mThreads;
        RingQueue<TaskNodeBase*> mHighPriorityTasks;
        RingQueue<TaskNodeBase*> mLowPriorityTasks;

        std::mutex mMutex;
        std::condition_variable mCondition;
        bool bExit = false;
    };
}