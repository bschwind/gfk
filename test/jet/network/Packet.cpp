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


// JetInputPacketReq
JetInputPacketReq::JetInputPacketReq() :
Packet(Packet::JET_INPUT_REQ),
throttleAmt(0.0f),
rollInput(0.0f),
pitchInput(0.0f),
yawInput(0.0f),
thrusterEnabled(0)
{

}

JetInputPacketReq::JetInputPacketReq(float throttleAmt, float rollInput, float pitchInput, float yawInput, unsigned char thrusterEnabled, unsigned int updateCount) :
Packet(Packet::JET_INPUT_REQ),
throttleAmt(throttleAmt),
rollInput(rollInput),
pitchInput(pitchInput),
yawInput(yawInput),
thrusterEnabled(thrusterEnabled),
updateCount()
{

}

void JetInputPacketReq::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteFloat32(throttleAmt);
	buffer.WriteFloat32(rollInput);
	buffer.WriteFloat32(pitchInput);
	buffer.WriteFloat32(yawInput);
	buffer.WriteUnsignedByte(thrusterEnabled);
	buffer.WriteUnsignedInt32(updateCount);
}


// Jet Input Response Packet
JetInputPacketRes::JetInputPacketRes(unsigned short id, const Vector3 &pos, const Quaternion &rot) :
Packet(Packet::JET_INPUT_RES),
id(id),
position(pos),
rotation(rot)
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
}

// Disconnect Packet
DisconnectPacket::DisconnectPacket() :
Packet(Packet::DISCONNECT_REQ)
{

}

void DisconnectPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

}
