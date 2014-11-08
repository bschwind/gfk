#include "network/Packet.hpp"

namespace jetGame
{

// Base Packet Class
Packet::Packet(unsigned char protocol) :
protocol(protocol)
{

}

Packet::~Packet()
{

}

void Packet::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	buffer.WriteUnsignedByte(protocol);
}

unsigned char Packet::GetPacketType()
{
	return protocol;
}


// NewDesktopClientPacket
NewDesktopClientPacket::NewDesktopClientPacket(unsigned char number) :
Packet(Packets::NEW_DESKTOP_CLIENT),
number(number)
{

}

void NewDesktopClientPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedByte(number);
}

NewDesktopClientPacket NewDesktopClientPacket::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned char number = buffer.ReadUnsignedByte();
	return NewDesktopClientPacket(number);
}


// NewAndroidClientPacket
NewAndroidClientPacket::NewAndroidClientPacket(unsigned char number) :
Packet(Packets::NEW_ANDROID_CLIENT),
number(number)
{

}

void NewAndroidClientPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedByte(number);
}

NewAndroidClientPacket NewAndroidClientPacket::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned char number = buffer.ReadUnsignedByte();
	return NewAndroidClientPacket(number);
}


// NewDesktopClientAckPacket
NewDesktopClientAckPacket::NewDesktopClientAckPacket(unsigned char numPlayers) :
Packet(Packets::NEW_DESKTOP_CLIENT_ACK),
numPlayers(numPlayers)
{

}

void NewDesktopClientAckPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteUnsignedByte(numPlayers);
}

NewDesktopClientAckPacket NewDesktopClientAckPacket::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned char number = buffer.ReadUnsignedByte();
	return NewDesktopClientAckPacket(number);
}


// NewAndroidClientAckPacket
NewAndroidClientAckPacket::NewAndroidClientAckPacket(unsigned char numPlayers) :
Packet(Packets::NEW_ANDROID_CLIENT_ACK),
numPlayers(numPlayers)
{

}

void NewAndroidClientAckPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
    Packet::WriteToBuffer(buffer);
    buffer.WriteUnsignedByte(numPlayers);
}

NewAndroidClientAckPacket NewAndroidClientAckPacket::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	unsigned char number = buffer.ReadUnsignedByte();
	return NewAndroidClientAckPacket(number);
}


// JetInputPacket
JetInputPacket::JetInputPacket(float throttleAmt, float rollInput, float pitchInput, float yawInput, unsigned char thrusterEnabled) :
Packet(Packets::JET_INPUT),
throttleAmt(throttleAmt),
rollInput(rollInput),
pitchInput(pitchInput),
yawInput(yawInput),
thrusterEnabled(thrusterEnabled)
{

}

void JetInputPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
	buffer.WriteFloat32(throttleAmt);
	buffer.WriteFloat32(rollInput);
	buffer.WriteFloat32(pitchInput);
	buffer.WriteFloat32(yawInput);
	buffer.WriteUnsignedByte(thrusterEnabled);
}

JetInputPacket JetInputPacket::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	float throttleAmt = buffer.ReadFloat32();
	float rollInput = buffer.ReadFloat32();
	float pitchInput = buffer.ReadFloat32();
	float yawInput = buffer.ReadFloat32();
	float thrusterEnabled = buffer.ReadUnsignedByte();
	return JetInputPacket(throttleAmt, rollInput, pitchInput, yawInput, thrusterEnabled);
}


// Heartbeat Packet
HeartbeatPacket::HeartbeatPacket() :
Packet(Packets::HEARTBEAT)
{

}

void HeartbeatPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

HeartbeatPacket HeartbeatPacket::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return HeartbeatPacket();
}


// Disconnect Packet
DisconnectPacket::DisconnectPacket() :
Packet(Packets::DISCONNECT)
{

}

void DisconnectPacket::WriteToBuffer(gfk::NetworkBuffer &buffer) const
{
	Packet::WriteToBuffer(buffer);
}

DisconnectPacket DisconnectPacket::ReadFromBuffer(gfk::NetworkBuffer &buffer)
{
	return DisconnectPacket();
}

}
