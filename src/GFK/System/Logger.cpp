#include <GFK/System/Logger.hpp>
#include <stdio.h>
#include <stdarg.h>

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
	std::cout << message;
#endif
}

void Logger::Logf(const std::string &format, ...)
{
	va_list args;
	va_start(args, format);

#if defined(PLATFORM_ANDROID)
	__android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, format.c_str(), args);
#else
	vprintf(format.c_str(), args);
#endif

	va_end(args);
}

void Logger::LogError(const std::string &error)
{
#if defined(PLATFORM_ANDROID)
	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s", error.c_str());
#else
	std::cerr << error << std::endl;
#endif
}

void Logger::LogErrorf(const std::string &format, ...)
{
	va_list args;
	va_start(args, format);
	
#if defined(PLATFORM_ANDROID)
	__android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, format.c_str(), args);
#else
	vfprintf(stderr, format.c_str(), args);
#endif

	va_end(args);
}

}
