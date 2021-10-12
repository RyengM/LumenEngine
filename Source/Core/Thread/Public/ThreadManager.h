#pragma once
#include "RunnableThread.h"
#include <unordered_map>
#include <thread>

namespace Lumen::Core
{
	// Singleton, manage threads with name
	class ThreadManager
	{
	public:
		static ThreadManager& GetInstance();

		bool Register(RunnableThread* thread);
		bool UnRegister(std::thread::id);

	private:
		ThreadManager() {}
		~ThreadManager() {}
		ThreadManager(ThreadManager&) = delete;
		ThreadManager& operator=(ThreadManager&) = delete;

	private:
		std::unordered_map<std::thread::id, RunnableThread*> mThreads;
	};
}