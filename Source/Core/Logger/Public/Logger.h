#pragma once
#include "ThirdParty/Spdlog/include/spdlog/spdlog.h"

namespace Lumen::Core
{
	// Logger singleton of spdlog
	class Logger
	{
	public:
		static Logger& GetInstance();

		inline std::shared_ptr<spdlog::logger> GetLogger() noexcept { return mLogger; }

	private:
		Logger();
		~Logger();
		Logger(const Logger&) = delete;
		Logger& operator=(const Logger&) = delete;

	private:
		std::shared_ptr<spdlog::logger> mLogger;
	};

#ifdef _Win32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)
#endif

#ifndef SUFFIX
#define SUFFIX(msg) std::string(msg).append("  Location: ").append(__FILENAME__).\
	append(" Line: ").append(std::to_string(__LINE__)).c_str()
#endif

#define LOG_INFO(...) Logger::GetInstance().GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) Logger::GetInstance().GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger::GetInstance().GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) Logger::GetInstance().GetLogger()->critical(__VA_ARGS__)
#define LOG_DEBUG(...) Logger::GetInstance().GetLogger()->debug(__VA_ARGS__)
#define LOG_TRACE(msg, ...) Logger::GetInstance().GetLogger()->trace(SUFFIX(msg), __VA_ARGS__)
#define LOG_FLUSH Logger::GetInstance().GetLogger()->flush()
}