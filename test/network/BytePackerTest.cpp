#include <iostream>
#include <GFK/Network/BytePacker.hpp>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main()
{
	std::cout.precision(64);

	float f = 3.1415926f;
	float unpackedFloat;
	unsigned long int packedFloat;

	double d = 3.14159265358979323;
	double unpackedDouble;
	unsigned long long int packedDouble;

	packedFloat = BytePacker::PackFloat(f);
	packedDouble = BytePacker::PackDouble(d);

	unpackedFloat = BytePacker::UnpackFloat(packedFloat);
	unpackedDouble = BytePacker::UnpackDouble(packedDouble);

	std::cout << "Original float:    " << f << std::endl;
	std::cout << "Packed float:      " << packedFloat << std::endl;
	std::cout << "Unpacked float:    " << unpackedFloat << std::endl;

	std::cout << "Original double    " << d << std::endl;
	std::cout << "Packed double:     " << packedDouble << std::endl;
	std::cout << "Unpacked double:   " << unpackedDouble << std::endl;

	std::cout << sizeof(packedFloat) << std::endl;
	std::cout << sizeof(packedDouble) << std::endl;
	
	return 0;
}
