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


// NewDesktopClientPacketReq
NewDesktopClientPacketReq::NewDesktopClientPacketReq() :
Packet(Packet::NEW_DESKTOP_CLIENT_REQ)
{

}

void NewDesktopClientPacketReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

NewDesktopClientPacketReq ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return NewDesktopClientPacketReq();
}


// NewAndroidClientPacketReq
NewAndroidClientPacketReq::NewAndroidClientPacketReq() :
Packet(Packet::NEW_ANDROID_CLIENT_REQ)
{

}

void NewAndroidClientPacketReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

NewAndroidClientPacketReq NewAndroidClientPacketReq::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return NewAndroidClientPacketReq();
}


// NewDesktopClientPacketRes
NewDesktopClientPacketRes::NewDesktopClientPacketRes(unsigned short id) :
Packet(Packet::NEW_DESKTOP_CLIENT_RES),
id(id)
{

}

void NewDesktopClientPacketRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

NewDesktopClientPacketRes NewDesktopClientPacketRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	NewDesktopClientPacketRes packet(buffer.ReadUnsignedInt16());

	return packet;
}


// NewAndroidClientPacketRes
NewAndroidClientPacketRes::NewAndroidClientPacketRes(unsigned short id) :
Packet(Packet::NEW_ANDROID_CLIENT_RES),
id(id)
{

}

void NewAndroidClientPacketRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

NewAndroidClientPacketRes NewAndroidClientPacketRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	NewAndroidClientPacketRes packet(buffer.ReadUnsignedInt16());

	return packet;
}


// GameInputPacketReq
GameInputPacketReq::GameInputPacketReq(const GameInput &input) :
Packet(Packet::GAME_INPUT_REQ),
input(input)
{

}

void GameInputPacketReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt32(input.sequenceNumber);
	buffer.WriteFloat32(input.mouseDiffX);
	buffer.WriteFloat32(input.mouseDiffY);

	// todo - put key presses in here
	unsigned int keyBitfield = 0;
	buffer.WriteUnsignedInt32(keyBitfield);
}

GameInputPacketReq GameInputPacketReq::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	GameInput input;
	input.sequenceNumber = buffer.ReadUnsignedInt32();
	input.mouseDiffX = buffer.ReadFloat32();
	input.mouseDiffY = buffer.ReadFloat32();
	unsigned int keyBitfield = buffer.ReadUnsignedInt32();
	// todo - read booleans from keyBitfield

	return GameInputPacketReq(input);
}


// JetInputPacketRes
JetInputPacketRes::JetInputPacketRes(unsigned short id, const Vector3 &pos, const Quaternion &rot, float engineRPM, unsigned int lastInputSequenceNumber) :
Packet(Packet::JET_INPUT_RES),
playerID(id),
position(pos),
rotation(rot),
engineRPM(engineRPM),
lastInputSequenceNumber(lastInputSequenceNumber)
{

}

void JetInputPacketRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);

	buffer.WriteUnsignedInt16(playerID);
	buffer.WriteVector3(position);
	buffer.WriteQuaternion(rotation);
	buffer.WriteFloat32(engineRPM);
	buffer.WriteUnsignedInt32(lastInputSequenceNumber);
}

JetInputPacketRes JetInputPacketRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned short id = buffer.ReadUnsignedInt16();
	Vector3 pos = buffer.ReadVector3();
	Quaternion rot = buffer.ReadQuaternion();
	float engineRPM = buffer.ReadFloat32();
	unsigned int sequenceNumber = buffer.ReadUnsignedInt32();

	return JetInputPacketRes(id, pos, rot, engineRPM, sequenceNumber);
}


// DisconnectPacketReq
DisconnectPacketReq::DisconnectPacketReq() :
Packet(Packet::DISCONNECT_REQ)
{

}

void DisconnectPacketReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

DisconnectPacketReq DisconnectPacketReq::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return DisconnectPacketReq();
}


// DisconnectPacketRes
DisconnectPacketRes::DisconnectPacketRes(unsigned short id) :
Packet(Packet::DISCONNECT_RES),
id(id)
{

}

void DisconnectPacketRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

DisconnectPacketRes DisconnectPacketRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return DisconnectPacketRes(buffer.ReadUnsignedInt16());
}


// ClientIdPacketRes
ClientIdPacketRes::ClientIdPacketRes(unsigned short id) :
Packet(Packet::CLIENT_ID_RES),
id(id)
{

}

void ClientIdPacketRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);
}

ClientIdPacketRes ClientIdPacketRes::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return ClientIdPacketRes(buffer.ReadUnsignedInt16());
}

}
