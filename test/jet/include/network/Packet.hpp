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
	static NewDesktopClientPacket ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewAndroidClientPacket : public Packet {
public:
	unsigned char number;

	NewAndroidClientPacket(unsigned char number);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewAndroidClientPacket ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewDesktopClientAckPacket : public Packet {
public:
	unsigned char numPlayers;

	NewDesktopClientAckPacket(unsigned char numPlayers);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewDesktopClientAckPacket ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewAndroidClientAckPacket : public Packet {
public:
    unsigned char numPlayers;

    NewAndroidClientAckPacket(unsigned char numPlayers);
    void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
    static NewAndroidClientAckPacket ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class JetInputPacket : public Packet {
public:
	float throttleAmt, rollInput, pitchInput, yawInput;
	unsigned char thrusterEnabled;
	
	JetInputPacket(float throttleAmt, float rollInput, float pitchInput, float yawInput, unsigned char thrusterEnabled);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static JetInputPacket ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class HeartbeatPacket : public Packet {
public:
	HeartbeatPacket();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static HeartbeatPacket ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class DisconnectPacket : public Packet {
public:
	DisconnectPacket();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static DisconnectPacket ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

}
