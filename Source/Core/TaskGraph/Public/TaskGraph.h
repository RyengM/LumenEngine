#pragma once

#include "Task.h"
#include "TaskThreadPool.h"
#include "Core/Memory/Public/MemoryPool.h"
#include <string>
#include <unordered_set>

#define TASK_ALLOC_SIZE 256				// Aligned size of task allocated in custom memory

namespace Lumen::Core
{
	// Task node in task graph
	template<typename T>
	class TaskNode : public TaskNodeBase
	{
	public:
		// Simply create a task
		// Task with dependency will be inserted in task graph
		// Task without dependency will be pushed to executing queue immediately
		static TaskNode<T>* CreateTask(std::string name, std::vector<size_t> denpendencies = {}, TaskPriority priority = TaskPriority::Low);
		~TaskNode() {};

		// Construct task and register node to task graph
		// @return handle of task
		template<typename... Args>
		TaskNode<T>* Schedual(Args... args);

		virtual void Wait() override;

		virtual void DoTask() override;

		virtual void AddSubsequence(size_t subsequence) override;
		virtual std::atomic<size_t> DecreaseDependenceCount() override { return --mUnExcutedDependencyCount; };
		virtual Task* GetTaskEntry() override { return (T*)&mTaskStorage; };
		virtual size_t GetIndex() override { return mIndex; }
		virtual size_t GetHash() override { return mHash; }
		virtual size_t GetDependenceCount() override { return mUnExcutedDependencyCount; }

	private:
		TaskNode() {}
		TaskNode(std::string name, std::vector<size_t> dependencies) : mName(std::move(name)), mDependencies(std::move(dependencies)) {}

		// Inform subsequent tasks when this task is done
		void Dispatch();

		// Clean task and set bDone to true
		void Finish();

	private:
		size_t mIndex;													// Identifier of task node
		size_t mHash;													// Hash of task typename
		std::string mName;
		TaskPriority mPriority;
		uint8_t mTaskStorage[sizeof(T)];								// Place where task data is stored
		std::vector<size_t> mDependencies;
		std::vector<size_t> mSubsequentTasks;
		std::atomic<size_t> mUnExcutedDependencyCount = 0;
		bool bDone = false;												// Fence
	};

	struct AlignedTaskWrapper
	{
		uint8_t padding[TASK_ALLOC_SIZE];
	};

	// Task allocator singleton, only used for task graph
	class TaskAllocator
	{
	public:
		static TaskAllocator& GetInstance();
		
		// Get a free address of memory pool
		AlignedTaskWrapper* Allocate();

		// Return the address to memory pool
		template<typename T>
		void Free(T* element);

	private:
		MemoryPool<AlignedTaskWrapper> mMemoryPool;
		bool bSetup = false;
	};

	// Task graph singleton, manage all the tasks with dependency
	class TaskGraph
	{
	public:
		static TaskGraph& GetInstance();
		// Ensure setup before using this singleton
		static void Setup(unsigned int threadNum);

		~TaskGraph() {}

		// Register node to map
		// @return index of Task
		template<typename T>
		size_t RegisterTask(T* node);

		// Unregister task from map
		void UnRegisterTask(size_t task);

		// Helper function, search task in mIndex2stallTaskMap, return nullptr if failed
		TaskNodeBase* SearchTask(size_t task);
		// Enqueue task to executing queue
		void EnqueueTask(size_t task, TaskPriority priority = TaskPriority::Low);

		void AddSubsequence(size_t task, size_t subsequence);

	private:
		TaskGraph() {};

	private:
		// Thread pool used for task graph
		TaskThreadPool* mThreadPool = nullptr;

		// Tasks with dependency unfinished or executing
		// Helper structure, used for grouping tasks with same typename
		// @size_t: hash of task typename, std::vector<TaskNodeBase*>: grouping task node
		std::unordered_map<size_t, std::vector<TaskNodeBase*>> mHash2stallTaskMap;
		// @size_t: index of task, TaskNodeBase*: task node
		std::unordered_map<size_t, TaskNodeBase*> mIndex2stallTaskMap;

		// This singleton must be setup before use
		bool bSetup = false;

		std::atomic<size_t> mRegisterCount = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
		std::mutex mMutex;
		std::condition_variable mCondition;
	};
}

#include "Details/TaskGraph.inl"