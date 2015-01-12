#include <GFK/Network/SocketHeader.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/BytePacker.hpp>
#include <GFK/Network/IPAddress.hpp>

namespace gfk
{

NetworkBuffer::NetworkBuffer(unsigned int capacity) :
bufferCapacity(capacity),
bufferCounter(0),
readCounter(0),
dataBuffer(capacity)
{
	
}

NetworkBuffer::~NetworkBuffer()
{

}

unsigned int NetworkBuffer::GetBufferCapacity()
{
	return bufferCapacity;
}

unsigned int NetworkBuffer::GetBufferCount()
{
	return bufferCounter;
}

unsigned char* NetworkBuffer::GetDataBuffer()
{
	return &dataBuffer[0];
}

void NetworkBuffer::WriteSignedByte(signed char c)
{
	dataBuffer[bufferCounter] = c;
	bufferCounter++;
}

void NetworkBuffer::WriteUnsignedByte(unsigned char c)
{
	dataBuffer[bufferCounter] = c;
	bufferCounter++;
}

void NetworkBuffer::WriteSignedInt16(signed short int i)
{
	i = htons(i);
	dataBuffer[bufferCounter]     = (i & 0xff00) >> 8;
	dataBuffer[bufferCounter + 1] = i & 0x00ff;
	bufferCounter += 2;
}

void NetworkBuffer::WriteUnsignedInt16(unsigned short int i)
{
	i = htons(i);
	dataBuffer[bufferCounter]     = (i & 0xff00) >> 8;
	dataBuffer[bufferCounter + 1] = i & 0x00ff;
	bufferCounter += 2;
}

void NetworkBuffer::WriteSignedInt32(signed int i)
{
	i = htonl(i);
	dataBuffer[bufferCounter]     = (i & 0xff000000) >> 24;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff0000) >> 16;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff00) >> 8;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff);
	bufferCounter += 4;
}

void NetworkBuffer::WriteUnsignedInt32(unsigned int i)
{
	i = htonl(i);
	dataBuffer[bufferCounter]     = (i & 0xff000000) >> 24;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff0000) >> 16;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff00) >> 8;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff);
	bufferCounter += 4;
}

void NetworkBuffer::WriteSignedInt64(signed long long int i)
{
	i = BytePacker::gfk_htonll(i);
	dataBuffer[bufferCounter]     = (i & 0xff00000000000000) >> 56;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff000000000000) >> 48;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff0000000000) >> 40;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff00000000) >> 32;
	dataBuffer[bufferCounter + 4] = (i & 0x00000000ff000000) >> 24;
	dataBuffer[bufferCounter + 5] = (i & 0x0000000000ff0000) >> 16;
	dataBuffer[bufferCounter + 6] = (i & 0x000000000000ff00) >> 8;
	dataBuffer[bufferCounter + 7] = (i & 0x00000000000000ff);
	bufferCounter += 8;

}

void NetworkBuffer::WriteUnsignedInt64(unsigned long long int i)
{
	i = BytePacker::gfk_htonll(i);
	dataBuffer[bufferCounter]     = (i & 0xff00000000000000) >> 56;
	dataBuffer[bufferCounter + 1] = (i & 0x00ff000000000000) >> 48;
	dataBuffer[bufferCounter + 2] = (i & 0x0000ff0000000000) >> 40;
	dataBuffer[bufferCounter + 3] = (i & 0x000000ff00000000) >> 32;
	dataBuffer[bufferCounter + 4] = (i & 0x00000000ff000000) >> 24;
	dataBuffer[bufferCounter + 5] = (i & 0x0000000000ff0000) >> 16;
	dataBuffer[bufferCounter + 6] = (i & 0x000000000000ff00) >> 8;
	dataBuffer[bufferCounter + 7] = (i & 0x00000000000000ff);
	bufferCounter += 8;
}

void NetworkBuffer::WriteFloat32(float f)
{
	WriteUnsignedInt32(BytePacker::PackFloat32(f));
}

void NetworkBuffer::WriteFloat64(double d)
{
	WriteUnsignedInt64(BytePacker::PackFloat64(d));
}

unsigned char NetworkBuffer::ReadUnsignedByte()
{
	unsigned char value = dataBuffer[readCounter];
	readCounter++;
	return value;
}

signed char NetworkBuffer::ReadSignedByte()
{
	signed char value = dataBuffer[readCounter];
	readCounter++;
	return value;
}

signed short int NetworkBuffer::ReadSignedInt16()
{
	signed short int value =
		(dataBuffer[readCounter] << 8)
		| dataBuffer[readCounter + 1];

	readCounter += 2;
	value = ntohs(value);
	return value;
}

unsigned short int NetworkBuffer::ReadUnsignedInt16()
{
	unsigned short int value =
		(dataBuffer[readCounter] << 8)
		| dataBuffer[readCounter + 1];

	readCounter += 2;
	value = ntohs(value);
	return value;
}

signed int NetworkBuffer::ReadSignedInt32()
{
	signed int value =
		(dataBuffer[readCounter] << 24)
		| (dataBuffer[readCounter + 1] << 16)
		| (dataBuffer[readCounter + 2] << 8)
		| dataBuffer[readCounter + 3];

	readCounter += 4;
	value = ntohl(value);
	return value;
}

unsigned int NetworkBuffer::ReadUnsignedInt32()
{
	unsigned int value =
		(dataBuffer[readCounter] << 24)
		| (dataBuffer[readCounter + 1] << 16)
		| (dataBuffer[readCounter + 2] << 8)
		| dataBuffer[readCounter + 3];

	readCounter += 4;
	value = ntohl(value);
	return value;
}

signed long long int NetworkBuffer::ReadSignedInt64()
{
	signed long long int value =
		((unsigned long long int)dataBuffer[readCounter] << 56)
		| ((unsigned long long int)dataBuffer[readCounter + 1] << 48)
		| ((unsigned long long int)dataBuffer[readCounter + 2] << 40)
		| ((unsigned long long int)dataBuffer[readCounter + 3] << 32)
		| ((unsigned long long int)dataBuffer[readCounter + 4] << 24)
		| ((unsigned long long int)dataBuffer[readCounter + 5] << 16)
		| ((unsigned long long int)dataBuffer[readCounter + 6] << 8)
		| (unsigned long long int)dataBuffer[readCounter + 7];

	readCounter += 8;
	value = static_cast<signed long long int>(BytePacker::gfk_ntohll(value));
	return value;
}

unsigned long long int NetworkBuffer::ReadUnsignedInt64()
{
	unsigned long long int value =
		((unsigned long long int)dataBuffer[readCounter] << 56)
		| ((unsigned long long int)dataBuffer[readCounter + 1] << 48)
		| ((unsigned long long int)dataBuffer[readCounter + 2] << 40)
		| ((unsigned long long int)dataBuffer[readCounter + 3] << 32)
		| ((unsigned long long int)dataBuffer[readCounter + 4] << 24)
		| ((unsigned long long int)dataBuffer[readCounter + 5] << 16)
		| ((unsigned long long int)dataBuffer[readCounter + 6] << 8)
		| (unsigned long long int)dataBuffer[readCounter + 7];

	readCounter += 8;
	value = BytePacker::gfk_ntohll(value);
	return value;
}

float NetworkBuffer::ReadFloat32()
{
	return BytePacker::UnpackFloat32(ReadUnsignedInt32());
}

double NetworkBuffer::ReadFloat64()
{
	return BytePacker::UnpackFloat64(ReadUnsignedInt64());
}

IPAddress NetworkBuffer::ReadAllPackets(const UDPSocket &socket)
{
	IPAddress sender;

	bufferCounter = 0;

	unsigned char *dataAddress = GetDataBuffer();
	unsigned int remainingSpace = GetBufferCapacity();

	while (true)
	{
		int byteReadCount = socket.Receive(sender, dataAddress, remainingSpace);
		bufferCounter += byteReadCount;
		dataAddress += byteReadCount;
		remainingSpace -= byteReadCount;

		if (!byteReadCount || remainingSpace <= 0)
		{
			break;
		}
	}

	return sender;
}

void NetworkBuffer::Reset()
{
	bufferCounter = 0;
	readCounter = 0;
}

}
