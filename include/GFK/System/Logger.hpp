#pragma once

#include <GFK/OSDetection.hpp>
#include <string>

namespace gfk
{

class Logger
{
public:
	static void Log(const std::string &message);
	static void LogError(const std::string &error);
};

}
