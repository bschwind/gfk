#include <GFK/System/Logger.hpp>

#if defined(PLATFORM_ANDROID)
	#include <android/log.h>

	#define LOG_TAG "libgfk"
#else
	#include <iostream>
#endif

namespace gfk
{

void Logger::Log(const std::string &message)
{
#if defined(PLATFORM_ANDROID)
	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s", message.c_str());
#else
	std::cout << message << std::endl;
#endif
}

void Logger::LogError(const std::string &error)
{
#if defined(PLATFORM_ANDROID)
	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", error.c_str());
#else
	std::cerr << error << std::endl;
#endif
}

}
