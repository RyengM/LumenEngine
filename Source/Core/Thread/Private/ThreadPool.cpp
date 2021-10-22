#include "Core/Thread/Public/ThreadPool.h"

#ifdef _MSC_VER
#include <windows.h>
#include <processthreadsapi.h>
#endif

using namespace Lumen::Core;

ThreadPool::ThreadPool(unsigned int num)
{
	mThreads.reserve(num);
	for (int i = 0; i < num; ++i)
	{
		mThreads.emplace_back([this] {
#ifdef _MSC_VER
			HRESULT r;
			r = SetThreadDescription(GetCurrentThread(), L"Thread Pool Worker Thread");
#endif
			while (true)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(mMutex);
					mCondition.wait(lock, [this] {
						return mTasks.Size() > 0 || bExit;
					});
					if (mTasks.Size() > 0)
					{
						task = std::move(mTasks.Front());
						mTasks.Pop();
					}
					if (bExit) return;
				}
				task();
			}
		});
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::lock_guard<std::mutex> lock(mMutex);
		bExit = true;
	}
	mCondition.notify_all();
	for (auto& thread : mThreads)
		thread.join();
}