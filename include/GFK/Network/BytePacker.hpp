#pragma once

namespace gfk
{

class BytePacker
{
public:
	static unsigned long int PackFloat(float f);
	static unsigned long long int PackDouble(double f);
	static float UnpackFloat(unsigned long int packedFloat);
	static double UnpackDouble(unsigned long long int packedDouble);
	static unsigned long long int htonll(unsigned long long int value);
	static unsigned long long int ntohll(unsigned long long int value);
private:
	static unsigned long long int Pack754(long double f, unsigned bits, unsigned expbits);
	static long double Unpack754(unsigned long long int i, unsigned bits, unsigned expbits);
};

}
