#include "Core/Thread/Public/RunnableThread.h"
#include "Core/Thread/Public/ThreadManager.h"

using namespace Lumen::Core;

RunnableThread* RunnableThread::Create(const char* name, Runnable* runnable)
{
	RunnableThread* thread = new RunnableThread(name, runnable);
	ThreadManager::GetInstance().Register(thread);
	return thread;
}

RunnableThread::RunnableThread() : mName(NULL), mRunnable(nullptr)
{

}

RunnableThread::RunnableThread(const char* name, Runnable* runnable) : mName(name), mRunnable(runnable)
{
	mThread = std::thread(&RunnableThread::Run, this);
	mThreadID = mThread.get_id();
	bInitialized = true;
}

RunnableThread::~RunnableThread()
{
	if (bInitialized) Exit();
}

void RunnableThread::Run()
{
	bool bRunnableInit = mRunnable->Init();
	while (bInitialized && !bStop && bRunnableInit) 
		mRunnable->Run();
}

void RunnableThread::Exit()
{
	bStop = true;
	mRunnable->Exit();
	ThreadManager::GetInstance().UnRegister(mThread.get_id());
	mThread.join();
	delete mRunnable;
}