#include "Core/TaskGraph/Public/TaskGraph.h"

using namespace Lumen::Core;

TaskAllocator& TaskAllocator::GetInstance()
{
    static TaskAllocator instance;
    return instance;
}

AlignedTaskWrapper* TaskAllocator::Allocate()
{
    return mMemoryPool.RequestElement();
}

TaskGraph& TaskGraph::GetInstance()
{
    static TaskGraph instance;
    return instance;
}

void TaskGraph::Setup(unsigned int threadNum)
{
    if (!TaskGraph::GetInstance().bSetup)
    {
        TaskGraph::GetInstance().mThreadPool = new TaskThreadPool(threadNum);
        TaskGraph::GetInstance().bSetup = true;
    }
}

TaskNodeBase* TaskGraph::SearchTask(size_t task)
{
    if (mIndex2stallTaskMap.find(task) != mIndex2stallTaskMap.end())
        return mIndex2stallTaskMap.at(task);
    return nullptr;
}

void TaskGraph::EnqueueTask(size_t task, TaskPriority priority)
{
    std::unique_lock<std::mutex> lock(mMutex);
    assert(mIndex2stallTaskMap.find(task) != mIndex2stallTaskMap.end());
    if (priority == TaskPriority::High)
        mThreadPool->Enqueue(mIndex2stallTaskMap.at(task), TaskPriority::High);
    else
        mThreadPool->Enqueue(mIndex2stallTaskMap.at(task), TaskPriority::Low);
}

void TaskGraph::AddSubsequence(size_t task, size_t subsequence)
{
    std::unique_lock<std::mutex> lock(mMutex);
    assert(mIndex2stallTaskMap.find(task) != mIndex2stallTaskMap.end());
    mIndex2stallTaskMap.at(task)->AddSubsequence(subsequence);
}

void TaskGraph::UnRegisterTask(size_t task)
{
    std::unique_lock<std::mutex> lock(mMutex);
    assert(mIndex2stallTaskMap.find(task) != mIndex2stallTaskMap.end());
    if (mHash2stallTaskMap.at(mIndex2stallTaskMap.at(task)->GetHash()).size() == 1)
        mHash2stallTaskMap.erase(mIndex2stallTaskMap.at(task)->GetHash());
    else
    {
        auto& vec = mHash2stallTaskMap.at(mIndex2stallTaskMap.at(task)->GetHash());
        for (int i = 0; i < vec.size(); ++i)
            if (vec[i]->GetIndex() == task)
                vec.erase(vec.begin() + i);
    }
    mIndex2stallTaskMap.erase(task);
}