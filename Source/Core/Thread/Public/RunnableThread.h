#pragma once

#include "Runnable.h"
#include <thread>

namespace Lumen::Core
{
    // Thread with name
    class RunnableThread
    {
    public:
        // Factory method to create a new runnable thread
        static RunnableThread* Create(const char* name, Runnable* runnable);

        RunnableThread();
        ~RunnableThread();

        void Exit();

        inline std::thread::id GetThreadID() noexcept { return mThreadID; }

    private:
        RunnableThread(const char* name, Runnable* runnable);
        
        void Run();

    private:
        const char* mName;
        std::thread mThread;
        std::thread::id mThreadID;

        Runnable* mRunnable;
        bool bInitialized = false;
        bool bStop = false;
    };
}