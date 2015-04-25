#include "network/Packet.hpp"

namespace jetGame
{

// Base Packet Class
Packet::Packet(unsigned short protocol) :
protocol(protocol)
{

}

Packet::~Packet()
{

}

void Packet::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	buffer.WriteUnsignedInt16(protocol);
}

unsigned short Packet::GetPacketType()
{
	return protocol;
}

// NewDesktopClientReq
NewDesktopClientReq::NewDesktopClientReq() :
Packet(Packet::NEW_DESKTOP_CLIENT_REQ)
{

}

void NewDesktopClientReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

NewDesktopClientReq NewDesktopClientReq::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return NewDesktopClientReq();
}

// NewDesktopClientRes
NewDesktopClientRes::NewDesktopClientRes(unsigned short id) :
Packet(Packet::NEW_DESKTOP_CLIENT_RES),
id(id)
{

}

void NewDesktopClientRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

NewDesktopClientRes NewDesktopClientRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned short id = buffer.ReadUnsignedInt16();
	return NewDesktopClientRes(id);
}

// NewAndroidClientReq
NewAndroidClientReq::NewAndroidClientReq() :
Packet(Packet::NEW_ANDROID_CLIENT_REQ)
{

}

void NewAndroidClientReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

NewAndroidClientReq NewAndroidClientReq::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return NewAndroidClientReq();
}

// NewAndroidClientRes
NewAndroidClientRes::NewAndroidClientRes(unsigned short id) :
Packet(Packet::NEW_ANDROID_CLIENT_RES),
id(id)
{

}

void NewAndroidClientRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

NewAndroidClientRes NewAndroidClientRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned short id = buffer.ReadUnsignedInt16();
	return NewAndroidClientRes(id);
}

// GameInputReq
GameInputReq::GameInputReq(unsigned int sequenceNumber, float mouseX, float mouseY, bool keyW, bool keyS, bool keyA, bool keyD, bool keyLeftShift) :
Packet(Packet::GAME_INPUT_REQ),
sequenceNumber(sequenceNumber),
mouseX(mouseX),
mouseY(mouseY),
keyW(keyW),
keyS(keyS),
keyA(keyA),
keyD(keyD),
keyLeftShift(keyLeftShift)
{

}

void GameInputReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt32(sequenceNumber);
	buffer.WriteFloat32(mouseX);
	buffer.WriteFloat32(mouseY);
	unsigned char bitfield = 0;
	bitfield |= (keyW ? (1 << 0) : 0);
	bitfield |= (keyS ? (1 << 1) : 0);
	bitfield |= (keyA ? (1 << 2) : 0);
	bitfield |= (keyD ? (1 << 3) : 0);
	bitfield |= (keyLeftShift ? (1 << 4) : 0);
	buffer.WriteUnsignedByte(bitfield);
}

GameInputReq GameInputReq::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned int sequenceNumber = buffer.ReadUnsignedInt32();
	float mouseX = buffer.ReadFloat32();
	float mouseY = buffer.ReadFloat32();
	unsigned char bitfield = buffer.ReadUnsignedByte();
	bool keyW = bitfield & (1 << 0);
	bool keyS = bitfield & (1 << 1);
	bool keyA = bitfield & (1 << 2);
	bool keyD = bitfield & (1 << 3);
	bool keyLeftShift = bitfield & (1 << 4);
	return GameInputReq(sequenceNumber, mouseX, mouseY, keyW, keyS, keyA, keyD, keyLeftShift);
}

// JetInputRes
JetInputRes::JetInputRes(unsigned short playerID, Vector3 position, Quaternion rotation, float engineRPM, unsigned int lastInputSequenceNumber) :
Packet(Packet::JET_INPUT_RES),
playerID(playerID),
position(position),
rotation(rotation),
engineRPM(engineRPM),
lastInputSequenceNumber(lastInputSequenceNumber)
{

}

void JetInputRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(playerID);
	buffer.WriteVector3(position);
	buffer.WriteQuaternion(rotation);
	buffer.WriteFloat32(engineRPM);
	buffer.WriteUnsignedInt32(lastInputSequenceNumber);
}

JetInputRes JetInputRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned short playerID = buffer.ReadUnsignedInt16();
	Vector3 position = buffer.ReadVector3();
	Quaternion rotation = buffer.ReadQuaternion();
	float engineRPM = buffer.ReadFloat32();
	unsigned int lastInputSequenceNumber = buffer.ReadUnsignedInt32();
	return JetInputRes(playerID, position, rotation, engineRPM, lastInputSequenceNumber);
}

// DisconnectReq
DisconnectReq::DisconnectReq() :
Packet(Packet::DISCONNECT_REQ)
{

}

void DisconnectReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

DisconnectReq DisconnectReq::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return DisconnectReq();
}

// DisconnectRes
DisconnectRes::DisconnectRes(unsigned short id) :
Packet(Packet::DISCONNECT_RES),
id(id)
{

}

void DisconnectRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

DisconnectRes DisconnectRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned short id = buffer.ReadUnsignedInt16();
	return DisconnectRes(id);
}

// ClientIdRes
ClientIdRes::ClientIdRes(unsigned short id) :
Packet(Packet::CLIENT_ID_RES),
id(id)
{

}

void ClientIdRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

ClientIdRes ClientIdRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned short id = buffer.ReadUnsignedInt16();
	return ClientIdRes(id);
}

}
