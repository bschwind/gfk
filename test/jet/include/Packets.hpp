#pragma once

namespace jetGame
{

class Packets
{
public:
	Packets();
	~Packets();

	static const unsigned int applicationID = 2124942189;
	static const unsigned char NEW_CLIENT = 0;
	static const unsigned char MOVEMENT = 1;
};

}