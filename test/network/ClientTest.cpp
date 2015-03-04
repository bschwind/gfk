#include <string>
#include <iostream>
#include <GFK/System/GameTime.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/System/Logger.hpp>

using namespace gfk;

int main(int argc, char* argv[])
{
	GameTime::InitClock();
	GameTime gameTime;

	std::cout.precision(16);

	UDPSocket::InitializeSocketLayer();

	UDPSocket socket;

	// Bind to 0 to get an OS-assigned port
	socket.Bind(0);

	// The destination will be the broadcast address at first to find the server
	IPAddress destination;
	int validAddress = IPAddress::FromIPV4String("127.0.0.1", 55777, destination);

	Logger::Logf("Destination is %s\n", destination.GetIPV4String().c_str());

	while (validAddress)
	{
		Logger::Log("Press enter to send a test packet\n");
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

		NetworkBuffer netBuffer(4096);
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

		socket.Send(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());
		double sentTime = gameTime.GetSystemTime();

		// Receive echo from server
		while (true)
		{
			int byteReadCount = socket.Receive(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

			if (!byteReadCount)
			{
				if (gameTime.GetSystemTime() - sentTime > 5)
				{
					Logger::Log("Server took too long to respond\n");
					netBuffer.Reset();
					break;
				}
				continue;
			}

			std::cout << "Echo back from server (" << byteReadCount << " bytes)" << std::endl;
			std::cout << "Server destination is " << destination.GetIPV4String() << std::endl;
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
