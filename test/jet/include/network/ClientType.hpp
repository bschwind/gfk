#pragma once

namespace jetGame
{

// todo - NDK compiler has issues with enums?
class ClientType
{
public:
	static const unsigned char DESKTOP = 0;
	static const unsigned char ANDROID = 1;
	static const unsigned char SERVER  = 2;
};

}
