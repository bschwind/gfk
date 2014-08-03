#include <string>
#include <iostream>
#include <GFK/Math/GUIDGenerator.hpp>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main()
{
	while (true)
	{
		Logger::Logf("%s\n", GUIDGenerator::GenerateGUID().c_str());
	}
	
	return 0;
}
