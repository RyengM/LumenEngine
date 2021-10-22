#pragma once
#include <atomic>

namespace Lumen::Core
{
	class Task
	{
	public:
		virtual void DoTask() = 0;
	};

	class TaskNodeBase
	{
	public:
		// Block thread until task is finished
		virtual void Wait() = 0;

		// Do task and destroy itself
		virtual void DoTask() = 0;

		virtual void AddSubsequence(size_t subsequence) = 0;
		virtual std::atomic<size_t> DecreaseDependenceCount() = 0;
		virtual Task* GetTaskEntry() = 0;
		virtual size_t GetIndex() = 0;
		virtual size_t GetHash() = 0;
		virtual size_t GetDependenceCount() = 0;
	};
}