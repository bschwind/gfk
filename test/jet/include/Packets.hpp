#pragma once

namespace jetGame
{

class Packets
{
public:
	Packets();
	~Packets();

	// 4 bytes each for applicationID, sequence, ack, ackBitField
	// 1 byte for numPackets
	static const unsigned int PACKET_HEADER_SIZE = 17;
	static const unsigned int applicationID = 2124942189;

	static const unsigned char NEW_DESKTOP_CLIENT = 0;
	static const unsigned char NEW_ANDROID_CLIENT = 1;
	static const unsigned char MOVEMENT = 2;
	static const unsigned char DISCONNECT = 3;
	static const unsigned char NEW_DESKTOP_CLIENT_ACK = 4;
	static const unsigned char NEW_ANDROID_CLIENT_ACK = 4;
};

}
