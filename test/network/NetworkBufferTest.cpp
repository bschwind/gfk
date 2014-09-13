#include <iostream>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/BytePacker.hpp>

using namespace gfk;

int main()
{
	std::cout.precision(32);

	signed char sbyte = -120;
	unsigned char ubyte = 77;
	signed short int ssi = -12000;
	unsigned short int usi = 64000;
	signed int si = -150000;
	unsigned int ui = 4000000;
	signed long long int sli = -800000;
	unsigned long long int uli = 370000000;
	float f = 3.1415926f;
	double d = 3.141592653589793;

	NetworkBuffer netBuffer(4096);
	netBuffer.WriteSignedByte(sbyte);
	netBuffer.WriteUnsignedByte(ubyte);
	netBuffer.WriteSignedInt16(ssi);
	netBuffer.WriteUnsignedInt16(usi);
	netBuffer.WriteSignedInt32(si);
	netBuffer.WriteUnsignedInt32(ui);
	netBuffer.WriteSignedInt64(sli);
	netBuffer.WriteUnsignedInt64(uli);
	netBuffer.WriteFloat32(f);
	netBuffer.WriteFloat64(d);

	std::cout << "Buffer size is " << netBuffer.GetBufferCount() << std::endl << std::endl;;

	std::cout << "Read signed byte: " << (int)netBuffer.ReadSignedByte() << std::endl;
	std::cout << "Read unsigned byte: " << (int)netBuffer.ReadUnsignedByte() << std::endl;
	std::cout << "Read signed short int " << netBuffer.ReadSignedInt16() << std::endl;
	std::cout << "Read unsigned short int " << netBuffer.ReadUnsignedInt16() << std::endl;
	std::cout << "Read signed int " << netBuffer.ReadSignedInt32() << std::endl;
	std::cout << "Read unsigned int " << netBuffer.ReadUnsignedInt32() << std::endl;
	std::cout << "Read signed long long int " << netBuffer.ReadSignedInt64() << std::endl;
	std::cout << "Read unsigned long long int " << netBuffer.ReadUnsignedInt64() << std::endl;
	std::cout << "Read float " << netBuffer.ReadFloat32() << std::endl;
	std::cout << "Read double " << netBuffer.ReadFloat64() << std::endl;

	std::cout << std::endl;
	
	return 0;
}
