#pragma once

namespace Lumen::Core
{
	template<typename T>
	TaskNode<T>* TaskNode<T>::CreateTask(std::string name, std::vector<size_t> dependencies, TaskPriority priority)
	{
		TaskNode<T>* node;
		if (sizeof(TaskNode<T>) <= TASK_ALLOC_SIZE)
		{
			node = reinterpret_cast<TaskNode<T>*>(TaskAllocator::GetInstance().Allocate());
			new(node)TaskNode<T>(name, dependencies);
		}
		else node = new TaskNode<T>();
		std::hash<std::string> hash;
		node->mHash = hash(typeid(T).name());
		node->mPriority = priority;
		return node;
	}

	template<typename T>
	template<typename... Args>
	TaskNode<T>* TaskNode<T>::Schedual(Args... args)
	{
		// Construct task
		new((void*)&mTaskStorage)T(std::forward<Args>(args)...);
		// Register node to task graph
		mIndex = TaskGraph::GetInstance().RegisterTask(this);
		// Build relationship between task node
		for (size_t& dependency : mDependencies)
		{
			// Find unfinished dependency, set its subsequent
			if (TaskGraph::GetInstance().SearchTask(dependency))
			{
				TaskGraph::GetInstance().AddSubsequence(dependency, mIndex);
				mUnExcutedDependencyCount++;
			}
			// If not find, this dependency is finished
			else dependency = -1;
		}
		// No dependency, add to execute queue
		if (mUnExcutedDependencyCount == 0)
			TaskGraph::GetInstance().EnqueueTask(mIndex, mPriority);
		return this;
	}

	template<typename T>
	void TaskNode<T>::AddSubsequence(size_t subsequence)
	{
		mSubsequentTasks.emplace_back(subsequence);
	}

	template<typename T>
	void TaskNode<T>::Wait()
	{
		while (!bDone) {}
	}

	template<typename T>
	void TaskNode<T>::DoTask()
	{
		T& task = *(T*)&mTaskStorage;
		task.DoTask();
		// Remove task from map
		TaskGraph::GetInstance().UnRegisterTask(mIndex);
		task.~T();
		Dispatch();
		Finish();
	}

	template<typename T>
	void TaskNode<T>::Dispatch()
	{
		for (auto subsequence : mSubsequentTasks)
		{
			TaskNodeBase* sub = TaskGraph::GetInstance().SearchTask(subsequence);
			if (sub)
			{
				if (sub->DecreaseDependenceCount() == 0)
					TaskGraph::GetInstance().EnqueueTask(subsequence);
			}
		}
	}

	template<typename T>
	void TaskNode<T>::Finish()
	{
		// Clean
		if (sizeof(TaskNode) <= TASK_ALLOC_SIZE)
		{
			this->~TaskNode();
			TaskAllocator::GetInstance().Free(this);
		}
		else delete this;
		// Set fence flag
		bDone = true;
	}

	template<typename T>
	void TaskAllocator::Free(T* element)
	{
		mMemoryPool.ReturnElement(reinterpret_cast<AlignedTaskWrapper*>(element));
	}

	template<typename T>
	size_t TaskGraph::RegisterTask(T* node)
	{
		std::unique_lock<std::mutex> lock(mMutex);

		assert(static_cast<TaskNodeBase*>(node));
		size_t index = mRegisterCount++;
		
		// Add node to stall task map
		mIndex2stallTaskMap.emplace(index, node);
		mHash2stallTaskMap[node->GetHash()].push_back(node);

		return index;
	}
}