#include <GFK/Network/SocketHeader.hpp>
#include <GFK/Network/BytePacker.hpp>

namespace gfk
{

// From beej's network guide:
// http://beej.us/guide/bgnet/output/html/multipage/advanced.html
unsigned long long int BytePacker::Pack754(long double f, unsigned bits, unsigned expbits)
{
	long double fnorm;
	int shift;
	long long sign, exp, significand;
	unsigned significandbits = bits - expbits - 1; // -1 for sign bit

	if (f == 0.0)
	{
		return 0; // get this special case out of the way
	}

	// check sign and begin normalization
	if (f < 0)
	{
		sign = 1;
		fnorm = -f;
	}
	else
	{
		sign = 0;
		fnorm = f;
	}

	// get the normalized form of f and track the exponent
	shift = 0;
	while (fnorm >= 2.0)
	{
		fnorm /= 2.0;
		shift++;
	}

	while (fnorm < 1.0)
	{
		fnorm *= 2.0;
		shift--;
	}

	fnorm = fnorm - 1.0;

	// calculate the binary form (non-float) of the significand data
	significand = fnorm * ((1LL << significandbits) + 0.5f);

	// get the biased exponent
	exp = shift + ((1 << (expbits-1)) - 1); // shift + bias

	// return the final answer
	return (sign << (bits-1)) | (exp << (bits-expbits-1)) | significand;
}

// From beej's network guide:
// http://beej.us/guide/bgnet/output/html/multipage/advanced.html
long double BytePacker::Unpack754(unsigned long long int i, unsigned bits, unsigned expbits)
{
	long double result;
	long long shift;
	unsigned bias;
	unsigned significandbits = bits - expbits - 1; // -1 for sign bit

	if (i == 0)
	{
		return 0.0;
	}

	// pull the significand
	result = (i & ((1LL << significandbits) - 1)); // mask
	result /= (1LL << significandbits); // convert back to float
	result += 1.0f; // add the one back on

	// deal with the exponent
	bias = (1 << (expbits - 1)) - 1;
	shift = ((i >> significandbits) & ((1LL << expbits) - 1)) - bias;
	while (shift > 0)
	{
		result *= 2.0;
		shift--;
	}

	while (shift < 0)
	{
		result /= 2.0;
		shift++;
	}

	// sign it
	result *= (i >> (bits - 1)) & 1 ? -1.0 : 1.0;

	return result;
}

unsigned long int BytePacker::PackFloat(float f)
{
	return Pack754(f, 32, 8);
}

unsigned long long int BytePacker::PackDouble(double d)
{
	return Pack754(d, 64, 11);
}

float BytePacker::UnpackFloat(unsigned long int packedFloat)
{
	return Unpack754(packedFloat, 32, 8);
}

double BytePacker::UnpackDouble(unsigned long long int packedDouble)
{
	return Unpack754(packedDouble, 64, 11);
}

// From http://stackoverflow.com/questions/3022552/is-there-any-standard-htonl-like-function-for-64-bits-integers-in-c
unsigned long long int BytePacker::htonll(unsigned long long int value)
{
	static const int num = 42;

	// Check the endianness
	if (*reinterpret_cast<const char*>(&num) == num)
	{
		const uint32_t high_part = htonl(static_cast<uint32_t>(value >> 32));
		const uint32_t low_part = htonl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));

		return (static_cast<unsigned long long int>(low_part) << 32) | high_part;
	}
	else
	{
		return value;
	}
}

// From http://stackoverflow.com/questions/3022552/is-there-any-standard-htonl-like-function-for-64-bits-integers-in-c
unsigned long long int BytePacker::ntohll(unsigned long long int value)
{
	static const int num = 42;

	// Check the endianness
	if (*reinterpret_cast<const char*>(&num) == num)
	{
		const uint32_t high_part = htonl(static_cast<uint32_t>(value >> 32));
		const uint32_t low_part = htonl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));

		return (static_cast<unsigned long long int>(low_part) << 32) | high_part;
	}
	else
	{
		return value;
	}
}

}
