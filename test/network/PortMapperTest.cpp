#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/Network/PortMapper.hpp>

using namespace gfk;

int main()
{
	std::cout.precision(16);

	PortMapper portMapper;
	portMapper.CreatePortMapping(8080);
	do
	{
		portMapper.Update();
	} while (!portMapper.IsActive());

	try {
		IPAddress address = portMapper.GetPublicIPAddress();
		std::cout << "Public address: " << address.GetIPV4String() << ":"
			  << address.GetPort() << std::endl;
	} catch (int errorCode) {
		std::cout << "Error while getting address";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(60000));

	return 0;
}
