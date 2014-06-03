#include <iostream>
#include <GFK/Network/BytePacker.hpp>
#include <GFK/System/Logger.hpp>
#include <bitset>

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

	std::cout << std::endl;

	std::cout << "Original double    " << d << std::endl;
	std::cout << "Packed double:     " << packedDouble << std::endl;
	std::cout << "Unpacked double:   " << unpackedDouble << std::endl;

	std::cout << std::endl;

	// Output endian information
	static const int num = 42;

	// Check the endianness
	if (*reinterpret_cast<const char*>(&num) == num)
	{
		std::cout << "This machine is little endian" << std::endl;
	}
	else
	{
		std::cout << "This machine is big endian" << std::endl;
	}

	std::cout << std::endl;

	packedDouble = 1;
	std::bitset<64> doubleBitset(packedDouble);
	std::cout << "64 bit int (1) in binary host order: " << doubleBitset << std::endl;

	std::cout << "Packed 64 bit double host:           " << packedDouble << std::endl;
	std::cout << "Packed 64 bit double network:        " << BytePacker::htonll(packedDouble) << std::endl;
	std::cout << "Packed 64 bit double host again:     " << BytePacker::ntohll(BytePacker::htonll(packedDouble)) << std::endl;

	std::cout << std::endl;

	packedFloat = 1;
	std::bitset<32> floatBitset(packedFloat);
	std::cout << "32 bit int (1) in binary host order: " << floatBitset << std::endl;

	std::cout << "Packed 32 bit float host:            " << packedFloat << std::endl;
	std::cout << "Packed 32 bit float network:         " << htonl(packedFloat) << std::endl;
	std::cout << "Packed 32 bit float host again:      " << ntohl(htonl(packedFloat)) << std::endl;
	
	return 0;
}
