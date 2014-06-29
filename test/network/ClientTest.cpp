#include <string>
#include <iostream>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		Logger::Log("Please provide a port to bind the client to");
		return 1;
	}

	std::cout.precision(16);

	int portInt = atoi(argv[1]);
	unsigned short port = (unsigned short)portInt;

	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;
	socket.Bind(port);

	IPAddress sender;
	IPAddress destination;
	int validAddress = IPAddress::FromIPV4String("192.168.1.255", 55777, destination);

	Logger::Log(std::string("Destination is ") + destination.GetIPV4String());

	while (validAddress)
	{
		std::cout << "Press enter to send a test packet" << std::endl;
		std::string message;
		std::getline(std::cin, message);

		signed char sbyte = -120;
		unsigned char ubyte = 77;
		signed short int ssi = -12000;
		unsigned short int usi = 64000;
		signed int si = -150000;
		unsigned int ui = 4000000;
		signed long long int sli = -800000;
		unsigned long long int uli = 370000000;
		float f = 3.1415926f;
		double d = 3.141592653589793;

		NetworkBuffer netBuffer;
		netBuffer.WriteSignedByte(sbyte);
		netBuffer.WriteUnsignedByte(ubyte);
		netBuffer.WriteSignedInt16(ssi);
		netBuffer.WriteUnsignedInt16(usi);
		netBuffer.WriteSignedInt32(si);
		netBuffer.WriteUnsignedInt32(ui);
		netBuffer.WriteSignedInt64(sli);
		netBuffer.WriteUnsignedInt64(uli);
		netBuffer.WriteFloat32(f);
		netBuffer.WriteFloat64(d);

		socket.Send(destination, netBuffer.GetDataBuffer(), 1024);

		// Receive echo from server
		while (true)
		{
			int byteReadCount = socket.Receive(sender, netBuffer.GetDataBuffer(), 1024); // 1024 should really be buffer size

			if (!byteReadCount)
			{
				continue;
			}

			std::cout << "Echo back from server (" << byteReadCount << " bytes)" << std::endl;
			std::cout << "--------Received Packet--------" << std::endl;
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
			std::cout << "--------End Packet ------------" << std::endl;

			netBuffer.Reset();

			break;
		}
	}

	UDPSocket::ShutdownSocketLayer();

	return 0;
}
