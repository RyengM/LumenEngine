#include "Core/Common/Public/RingQueue.h"
#include <vector>

using namespace Lumen::Core;

int Test(int a) { return a; }

void main()
{
	struct TestStruct
	{
		TestStruct() {}
		TestStruct(int in) : a(in) {}
		int a = 0;
		std::vector<float> b;
	};
	
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
}