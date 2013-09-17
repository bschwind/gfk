#include <string>
#include <iostream>
#include <GFK/Math/GUIDGenerator.hpp>

using namespace gfk;

int main()
{
	while (true)
	{
		std::cout << GUIDGenerator::GenerateGUID() << std::endl;
	}
	
	return 0;
}
