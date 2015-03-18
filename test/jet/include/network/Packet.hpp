#pragma once

#include "objects/GameInput.hpp"
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
	static const unsigned short GAME_INPUT_REQ = 6;
	static const unsigned short JET_INPUT_RES = 7;
	static const unsigned short CLIENT_ID_RES = 8;

	unsigned short GetPacketType();
	virtual void WriteToBuffer(gfk::NetworkBuffer &buffer) const;

	unsigned short protocol;
};

class NewDesktopClientPacketReq : public Packet {
public:
	NewDesktopClientPacketReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewDesktopClientPacketReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewAndroidClientPacketReq : public Packet {
public:
	NewAndroidClientPacketReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewAndroidClientPacketReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewDesktopClientPacketRes : public Packet {
public:
	unsigned short id;

	NewDesktopClientPacketRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewDesktopClientPacketRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewAndroidClientPacketRes : public Packet {
public:
    unsigned short id;

    NewAndroidClientPacketRes(unsigned short id);
    void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
    static NewAndroidClientPacketRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class GameInputPacketReq : public Packet {
public:
	GameInput input;

	GameInputPacketReq(const GameInput &input);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static GameInputPacketReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class JetInputPacketRes : public Packet {
public:
	unsigned short playerID;
	Vector3 position;
	Quaternion rotation;
	float engineRPM;
	unsigned int lastInputSequenceNumber;

	JetInputPacketRes(unsigned short id, const Vector3 &pos, const Quaternion &rot, float engineRPM, unsigned int lastInputSequenceNumber);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static JetInputPacketRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class DisconnectPacketReq : public Packet {
public:
	DisconnectPacketReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static DisconnectPacketReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class DisconnectPacketRes : public Packet {
public:
	unsigned short id;
	DisconnectPacketRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static DisconnectPacketRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class ClientIdPacketRes : public Packet {
public:
	unsigned short id;
	ClientIdPacketRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static ClientIdPacketRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

}
