#include "Core/Thread/Public/ThreadManager.h"

using namespace Lumen::Core;

ThreadManager& ThreadManager::GetInstance()
{
	static ThreadManager instance;
	return instance;
}

void ThreadManager::Register(RunnableThread* thread)
{
	mThreads.emplace(thread->GetThreadID(), thread);
}

void ThreadManager::UnRegister(std::thread::id id)
{
	mThreads.erase(id);
}