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


// NewAndroidClientPacketReq
NewAndroidClientPacketReq::NewAndroidClientPacketReq() :
Packet(Packet::NEW_ANDROID_CLIENT_REQ)
{

}

void NewAndroidClientPacketReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
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


// Game Input Request Packet
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


// Jet Input Response Packet
JetInputPacketRes::JetInputPacketRes(unsigned short id, const Vector3 &pos, const Quaternion &rot, float engineRPM, unsigned int lastInputSequenceNumber) :
Packet(Packet::JET_INPUT_RES),
id(id),
position(pos),
rotation(rot),
engineRPM(engineRPM),
lastInputSequenceNumber(lastInputSequenceNumber)
{

}

void JetInputPacketRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedInt16(id);

	buffer.WriteFloat32(position.X);
	buffer.WriteFloat32(position.Y);
	buffer.WriteFloat32(position.Z);

	buffer.WriteFloat32(rotation.X);
	buffer.WriteFloat32(rotation.Y);
	buffer.WriteFloat32(rotation.Z);
	buffer.WriteFloat32(rotation.W);

	buffer.WriteFloat32(engineRPM);

	buffer.WriteUnsignedInt32(lastInputSequenceNumber);
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

}
