#pragma once

namespace Lumen::Core
{
	// Singleton, manage all threads
	class ThreadManager
	{
	public:
		static ThreadManager& GetInstance();

	private:
		ThreadManager() {}
		~ThreadManager() {}
		ThreadManager(ThreadManager&) = delete;
		ThreadManager& operator=(ThreadManager&) = delete;

	private:

	};
}