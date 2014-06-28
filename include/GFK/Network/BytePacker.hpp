#pragma once

namespace gfk
{

class BytePacker
{
public:
	static unsigned int PackFloat32(float f);
	static unsigned long int PackFloat64(double f);
	static float UnpackFloat32(unsigned int packedFloat);
	static double UnpackFloat64(unsigned long int packedDouble);
	static unsigned long int htonll(unsigned long int value);
	static unsigned long int ntohll(unsigned long int value);
private:
	static unsigned long long int Pack754(long double f, unsigned bits, unsigned expbits);
	static long double Unpack754(unsigned long long int i, unsigned bits, unsigned expbits);
};

}
