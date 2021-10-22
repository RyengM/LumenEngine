#include "Core/TaskGraph/Public/TaskThreadPool.h"

#ifdef _MSC_VER
#include <windows.h>
#include <processthreadsapi.h>
#endif

using namespace Lumen::Core;

TaskThreadPool::TaskThreadPool(unsigned int num)
{
	mThreads.reserve(num);
	for (int i = 0; i < num; ++i)
	{
		mThreads.emplace_back([this, i] {
#ifdef _MSC_VER
			HRESULT r;
			r = SetThreadDescription(GetCurrentThread(), L"Task Graph Worker Thread");
#endif
			while (true)
			{
				TaskNodeBase* task;
				{
					std::unique_lock<std::mutex> lock(mMutex);
					mCondition.wait(lock, [this] {
						return mLowPriorityTasks.Size() > 0 || mHighPriorityTasks.Size() > 0 || bExit;
					});
					if (mHighPriorityTasks.Size() > 0)
					{
						task = std::move(mHighPriorityTasks.Front());
						mHighPriorityTasks.Pop();
					}
					else
					{
						task = std::move(mLowPriorityTasks.Front());
						mLowPriorityTasks.Pop();
					}
					if (bExit) return;
				}
				task->DoTask();
			}
		});
	}
}

TaskThreadPool::~TaskThreadPool()
{
	{
		std::lock_guard<std::mutex> lock(mMutex);
		bExit = true;
	}
	mCondition.notify_all();
	for (auto& thread : mThreads)
		thread.join();
}

void TaskThreadPool::Enqueue(TaskNodeBase* task, TaskPriority priority)
{
	{
		std::unique_lock<std::mutex> lock(mMutex);
		if (priority == TaskPriority::High)
			mHighPriorityTasks.Emplace(task);
		else
			mLowPriorityTasks.Emplace(task);
	}
	mCondition.notify_one();
}