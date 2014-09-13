#pragma once

#include <GFK/Network/NetworkBuffer.hpp>
#include "Packets.hpp"

namespace jetGame
{

class Packet
{
public:
	Packet(unsigned char protocol);
	~Packet();

	unsigned char GetPacketType();
	virtual void WriteToBuffer(gfk::NetworkBuffer &buffer) const;

	unsigned int applicationID;
	unsigned int sequence;
	unsigned int ack;
	unsigned int ackBitfield;
	unsigned char protocol;
};

class NewDesktopClientPacket : public Packet {
public:
	unsigned char number;

	NewDesktopClientPacket(unsigned char number);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class NewAndroidClientPacket : public Packet {
public:
	unsigned char number;

	NewAndroidClientPacket(unsigned char number);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class NewDesktopClientAckPacket : public Packet {
public:
	unsigned char numPlayers;

	NewDesktopClientAckPacket(unsigned char numPlayers);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class NewAndroidClientAckPacket : public Packet {
public:
    unsigned char numPlayers;

    NewAndroidClientAckPacket(unsigned char numPlayers);
    void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class MovementPacket : public Packet {
public:
	float x, y, z;
	
	MovementPacket(float x, float y, float z);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class DisconnectPacket : public Packet {
public:
	DisconnectPacket();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

}
