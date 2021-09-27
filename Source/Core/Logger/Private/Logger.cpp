#include "Core/Logger/Public/Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <time.h>
#include <vector>
#include <sstream>

using namespace Lumen::Core;

Logger::Logger()
{
	std::vector<spdlog::sink_ptr> sinkList;

	auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	consoleSink->set_level(spdlog::level::trace);
	consoleSink->set_pattern("[%Y-%m-%d %T.%e][%^%l%$][%n] %v");
	sinkList.emplace_back(consoleSink);

	std::ostringstream oss;
	time_t time = std::time(NULL);
	struct tm* t = std::localtime(&time);
	oss << t->tm_year + 1900 << "." << t->tm_mon + 1 << "." << t->tm_mday << "-" <<
		t->tm_hour << "." << t->tm_min << "." << t->tm_sec;
	std::string filename = "Logs/Lumen-Log-" + oss.str() + ".log";
	auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);
	fileSink->set_level(spdlog::level::trace);
	fileSink->set_pattern("[%Y-%m-%d %T.%e][%^%l%$][%n] %v");
	sinkList.emplace_back(fileSink);

	mLogger = std::make_shared<spdlog::logger>("logger", sinkList.begin(), sinkList.end());
	spdlog::register_logger(mLogger);

	mLogger->set_level(spdlog::level::trace);

	mLogger->flush_on(spdlog::level::err);
}

Logger::~Logger()
{
	spdlog::drop_all();
}

Logger& Logger::GetInstance()
{
	static Logger instance;
	return instance;
}