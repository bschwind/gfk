#include <string>
#include <iostream>
#include <GFK/Math/GUIDGenerator.hpp>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main()
{
	while (true)
	{
		Logger::Log(GUIDGenerator::GenerateGUID());
	}
	
	return 0;
}
