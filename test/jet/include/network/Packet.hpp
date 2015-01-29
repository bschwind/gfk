#pragma once

#include <GFK/Network/NetworkBuffer.hpp>

namespace jetGame
{

class Packet
{
public:
	Packet(unsigned short protocol);
	~Packet();

	static const unsigned short NEW_DESKTOP_CLIENT_REQ = 0;
	static const unsigned short NEW_DESKTOP_CLIENT_RES = 1;
	static const unsigned short NEW_ANDROID_CLIENT_REQ = 2;
	static const unsigned short NEW_ANDROID_CLIENT_RES = 3;
	static const unsigned short DISCONNECT_REQ = 4;
	static const unsigned short DISCONNECT_RES = 5;
	static const unsigned short JET_INPUT_REQ = 6;
	static const unsigned short JET_INPUT_RES = 7;

	unsigned short GetPacketType();
	virtual void WriteToBuffer(gfk::NetworkBuffer &buffer) const;

	unsigned short protocol;
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

class JetInputPacketReq : public Packet {
public:
	float throttleAmt;
	float rollInput;
	float pitchInput;
	float yawInput;
	unsigned char thrusterEnabled; // 0 - false, 1 - true
	
	JetInputPacketReq();
	JetInputPacketReq(float throttleAmt, float rollInput, float pitchInput, float yawInput, unsigned char thrusterEnabled);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class JetInputPacketRes : public Packet {
public:
	float x, y, z;

	JetInputPacketRes(float x, float y, float z);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class DisconnectPacket : public Packet {
public:
	DisconnectPacket();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

}
