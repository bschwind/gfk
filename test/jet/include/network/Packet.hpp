#pragma once

#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>

using namespace gfk;

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

class NewDesktopClientPacketReq : public Packet {
public:
	NewDesktopClientPacketReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class NewAndroidClientPacketReq : public Packet {
public:
	NewAndroidClientPacketReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class NewDesktopClientPacketRes : public Packet {
public:
	unsigned short id;

	NewDesktopClientPacketRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class NewAndroidClientPacketRes : public Packet {
public:
    unsigned short id;

    NewAndroidClientPacketRes(unsigned short id);
    void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class JetInputPacketReq : public Packet {
public:
	float throttleAmt;
	float rollInput;
	float pitchInput;
	float yawInput;
	unsigned char thrusterEnabled; // 0 - false, 1 - true
	unsigned int updateCount;
	
	JetInputPacketReq();
	JetInputPacketReq(float throttleAmt, float rollInput, float pitchInput, float yawInput, unsigned char thrusterEnabled, unsigned int updateCount);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class JetInputPacketRes : public Packet {
public:
	unsigned short id;
	Vector3 position;
	Quaternion rotation;

	JetInputPacketRes(unsigned short id, const Vector3 &pos, const Quaternion &rot);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

class DisconnectPacket : public Packet {
public:
	DisconnectPacket();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
};

}
