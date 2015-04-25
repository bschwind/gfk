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
	static const unsigned short GAME_INPUT_REQ = 4;
	static const unsigned short JET_INPUT_RES = 5;
	static const unsigned short DISCONNECT_REQ = 6;
	static const unsigned short DISCONNECT_RES = 7;
	static const unsigned short CLIENT_ID_RES = 8;

	unsigned short GetPacketType();
	virtual void WriteToBuffer(gfk::NetworkBuffer &buffer) const;

	unsigned short protocol;
};

class NewDesktopClientReq : public Packet {
public:
	NewDesktopClientReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewDesktopClientReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewDesktopClientRes : public Packet {
public:
	unsigned short id;

	NewDesktopClientRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewDesktopClientRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewAndroidClientReq : public Packet {
public:
	NewAndroidClientReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewAndroidClientReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class NewAndroidClientRes : public Packet {
public:
	unsigned short id;

	NewAndroidClientRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static NewAndroidClientRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class GameInputReq : public Packet {
public:
	unsigned int sequenceNumber;
	float mouseX;
	float mouseY;
	bool keyW;
	bool keyS;
	bool keyA;
	bool keyD;
	bool keyLeftShift;

	GameInputReq(unsigned int sequenceNumber, float mouseX, float mouseY, bool keyW, bool keyS, bool keyA, bool keyD, bool keyLeftShift);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static GameInputReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class JetInputRes : public Packet {
public:
	unsigned short playerID;
	Vector3 position;
	Quaternion rotation;
	float engineRPM;
	unsigned int lastInputSequenceNumber;

	JetInputRes(unsigned short playerID, Vector3 position, Quaternion rotation, float engineRPM, unsigned int lastInputSequenceNumber);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static JetInputRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class DisconnectReq : public Packet {
public:
	DisconnectReq();
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static DisconnectReq ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class DisconnectRes : public Packet {
public:
	unsigned short id;

	DisconnectRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static DisconnectRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

class ClientIdRes : public Packet {
public:
	unsigned short id;

	ClientIdRes(unsigned short id);
	void WriteToBuffer(gfk::NetworkBuffer &buffer) const;
	static ClientIdRes ReadFromBuffer(gfk::NetworkBuffer &buffer);
};

}
