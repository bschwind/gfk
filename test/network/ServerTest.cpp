#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>

using namespace gfk;

int main()
{
	std::cout.precision(16);

	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;
	socket.Bind(55777);

	NetworkBuffer netBuffer(4096);

	IPAddress sender;
	while (true)
	{
		int byteReadCount = socket.Receive(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());
		if (!byteReadCount)
		{
			continue;
		}

		// Echo the contents back to the client immediately
		socket.Send(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCount());

		std::cout << "--------Received Packet (from " << sender.GetIPV4String() << ")" << std::endl;
		std::cout << "Read signed byte: " << (int)netBuffer.ReadSignedByte() << std::endl;
		std::cout << "Read unsigned byte: " << (int)netBuffer.ReadUnsignedByte() << std::endl;
		std::cout << "Read signed short int " << netBuffer.ReadSignedInt16() << std::endl;
		std::cout << "Read unsigned short int " << netBuffer.ReadUnsignedInt16() << std::endl;
		std::cout << "Read signed int " << netBuffer.ReadSignedInt32() << std::endl;
		std::cout << "Read unsigned int " << netBuffer.ReadUnsignedInt32() << std::endl;
		std::cout << "Read signed long long int " << netBuffer.ReadSignedInt64() << std::endl;
		std::cout << "Read unsigned long long int " << netBuffer.ReadUnsignedInt64() << std::endl;
		std::cout << "Read float " << netBuffer.ReadFloat32() << std::endl;
		std::cout << "Read double " << netBuffer.ReadFloat64() << std::endl;
		std::cout << "--------End Packet --------------------" << std::endl;

		netBuffer.Reset();
	}

	UDPSocket::ShutdownSocketLayer();
	
	return 0;
}
