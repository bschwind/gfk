#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/PortMapping.hpp>

using namespace gfk;

int main()
{
	std::cout.precision(16);

	PortMapping portMapping;
	portMapping.Create(8080);
	do
	{
		portMapping.Update();
	} while (!portMapping.IsMapped());

	try {
		IPAddress address = portMapping.GetPublicIPAddress();
		std::cout << "Public address: " << address.GetIPV4String() << ":"
			  << address.GetPort() << std::endl;
	} catch (int errorCode) {
		std::cout << "Error while getting address";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(60000));

	return 0;
}
