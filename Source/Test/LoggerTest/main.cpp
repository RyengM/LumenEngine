#include "Core/Logger/Public/Logger.h"
#include <iostream>

using namespace Lumen::Core;

int main()
{
	Logger::GetInstance().GetLogger()->set_level(spdlog::level::info);
	Logger::GetInstance().GetLogger()->set_level(spdlog::level::trace);
	LOG_INFO("233");
	LOG_WARN("233");
	LOG_ERROR("233");
	LOG_DEBUG("233");
	LOG_CRITICAL("233");
	LOG_FLUSH;
	LOG_TRACE("233");

	return 0;
}