#include "Core/Common/Public/RingQueue.h"
#include "Core/Thread/Public/ThreadPool.h"
#include "Core/Thread/Public/RunnableThread.h"
#include "Core/TaskGraph/Public/TaskGraph.h"
#include <vector>
#include <string>
#include <iostream>

using namespace Lumen::Core;

int Test(int a) { return a; }

class TestRunnable : public Runnable
{
public:
	virtual void Run() override { std::cout << std::to_string(a++) << std::endl; }
	virtual void Stop() override {}
	virtual void Exit() override {}
	virtual ~TestRunnable() override {}

private:
	int a = 0;
};

class TestTaskA : public Task
{
public:
	virtual void DoTask() override
	{
		std::cout << "test task A" << std::endl;
	}
};

class TestTaskB : public Task
{
public:
	TestTaskB() {}
	TestTaskB(std::string str) : mStr(str) {}

	virtual void DoTask() override
	{
		std::cout << "test task B " + mStr << std::endl;
	}

private:
	std::string mStr;
};

class TestTaskC : public Task
{
public:
	TestTaskC(std::string str) : mStr(str) {}

	virtual void DoTask() override
	{
		std::cout << "test task C " + mStr << std::endl;
	}

private:
	std::string mStr;
};

int main()
{
	struct TestStruct
	{
		TestStruct() {}
		TestStruct(int in) : a(in) {}
		int a = 0;
		std::vector<float> b;
	};
	
	// Ring queue test
	{
		RingQueue<TestStruct> queue;
		queue.Push(TestStruct());
		TestStruct s = queue.Front();
		queue.Push(TestStruct(1));
		int v0 = queue.GetBuffer()->item.a;
		int v1 = (queue.GetBuffer() + 1)->item.a;
		queue.Pop();
		queue.Push(TestStruct(2));
		v0 = queue.GetBuffer()->item.a;
		v1 = (queue.GetBuffer() + 1)->item.a;
		queue.Clear();
		queue.Reserve(10);
		queue.Emplace(2);
	}

	{
		typedef int (*funcPtr)(int);
		funcPtr p = Test;
		RingQueue<funcPtr> q;
		q.Push(p);
		int v0 = q.Front()(2);
		int v1 = q.GetBuffer()->item(3);
	}

	{
		RingQueue<TestStruct> queue;
		queue.Push(TestStruct(1));
		auto t = std::move(queue.Front());
		queue.Pop();
		int a = 2;
	}

	// Thread pool test
	{
		ThreadPool pool(4);
		std::vector<std::future<int>> results;

		for (int i = 0; i < 4; ++i) 
		{
			results.emplace_back(
				pool.Enqueue([i]() {
					std::cout << "[" + std::to_string(i) + "] start" << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(1));
					std::cout << "[" + std::to_string(i) + "] end" << std::endl;
					return i;
				})
			);
		}

		for (auto&& result : results)
			std::cout << "[" + std::to_string(result.get()) + "] result" << std::endl;
	}

	// Runnable thread test
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		TestRunnable* runnable = new TestRunnable();
		RunnableThread* testThread = RunnableThread::Create("233", runnable);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		testThread->Exit();
	}

	// Task graph test
	{
		TaskGraph::Setup(4);
		auto taskRefA = TaskNode<TestTaskA>::CreateTask("TaskA")->Schedual();
		auto taskRefB = TaskNode<TestTaskB>::CreateTask("TaskB", {taskRefA->GetIndex()})->Schedual("233 B");
		auto taskRefC = TaskNode<TestTaskC>::CreateTask("TaskC", {taskRefB->GetIndex()})->Schedual("233 C");
		taskRefC->Wait();
	}

	return 0;
}