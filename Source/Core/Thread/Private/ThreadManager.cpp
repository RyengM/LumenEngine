#include "Core/Thread/Public/ThreadManager.h"

using namespace Lumen::Core;

ThreadManager& ThreadManager::GetInstance()
{
	static ThreadManager instance;
	return instance;
}

bool ThreadManager::Register(RunnableThread* thread)
{
	mThreads.insert({ thread->GetThreadID(), thread });
}

bool ThreadManager::UnRegister(std::thread::id id)
{
	mThreads.erase(id);
}