#pragma once
#include "Runnable.h"
#include <thread>

namespace Lumen::Core
{
	// Thread with name
	class RunnableThread
	{
	public:
		static RunnableThread* Create(const char* name, Runnable* runnable);



	private:
		const char* name;
		std::thread thread;
		Runnable* runnable;
	};
}