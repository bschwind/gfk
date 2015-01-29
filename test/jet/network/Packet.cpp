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


// NewDesktopClientPacket
NewDesktopClientPacket::NewDesktopClientPacket(unsigned char number) :
Packet(Packet::NEW_DESKTOP_CLIENT_REQ),
number(number)
{

}

void NewDesktopClientPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedByte(number);
}


// NewAndroidClientPacket
NewAndroidClientPacket::NewAndroidClientPacket(unsigned char number) :
Packet(Packet::NEW_ANDROID_CLIENT_REQ),
number(number)
{

}

void NewAndroidClientPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedByte(number);
}


// NewDesktopClientAckPacket
NewDesktopClientAckPacket::NewDesktopClientAckPacket(unsigned char numPlayers) :
Packet(Packet::NEW_DESKTOP_CLIENT_RES),
numPlayers(numPlayers)
{

}

void NewDesktopClientAckPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedByte(numPlayers);
}


// NewAndroidClientAckPacket
NewAndroidClientAckPacket::NewAndroidClientAckPacket(unsigned char numPlayers) :
Packet(Packet::NEW_ANDROID_CLIENT_RES),
numPlayers(numPlayers)
{

}

void NewAndroidClientAckPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
    Packet::WriteToBuffer(buffer);
    buffer.WriteUnsignedByte(numPlayers);
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

JetInputPacketReq::JetInputPacketReq(float throttleAmt, float rollInput, float pitchInput, float yawInput, unsigned char thrusterEnabled) :
Packet(Packet::JET_INPUT_REQ),
throttleAmt(throttleAmt),
rollInput(rollInput),
pitchInput(pitchInput),
yawInput(yawInput),
thrusterEnabled(thrusterEnabled)
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
}


// Jet Input Response Packet
JetInputPacketRes::JetInputPacketRes(float x, float y, float z) :
Packet(Packet::JET_INPUT_RES),
x(x),
y(y),
z(z)
{

}

void JetInputPacketRes::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteFloat32(x);
	buffer.WriteFloat32(y);
	buffer.WriteFloat32(z);
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
