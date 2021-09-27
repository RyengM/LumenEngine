#include "Core/Thread/Public/ThreadManager.h"

using namespace Lumen::Core;

ThreadManager& ThreadManager::GetInstance()
{
	static ThreadManager instance;
	return instance;
}