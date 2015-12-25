#pragma once

namespace jetGame
{

// todo - NDK compiler has issues with enums?
class ClientType
{
public:
	static const unsigned char DESKTOP = 0;
	static const unsigned char GFK_ANDROID = 1; // ANDROID is apparently a C macro in the NDK
	static const unsigned char SERVER  = 2;
};

}
