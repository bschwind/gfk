#include <GFK/System/GameTime.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/System/Logger.hpp>
#include <enet/enet.h>
#include <iostream>

namespace gfk
{

bool UDPSocket::socketsInitialized = false;

UDPSocket::UDPSocket() :
handle(0),
socketPort(0)
{

}

UDPSocket::~UDPSocket()
{
	Close();
}

bool UDPSocket::Bind(unsigned short port, bool blocking)
{
	if (IsOpen())
	{
		Close();
	}

	// Create the socket
	handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (handle <= 0)
	{
		Logger::LogErrorf("Failed to create a UDP socket on port %u\n", port);
		Close();
		return false;
	}

	// Bind the socket to a port
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		Logger::LogErrorf("Failed to bind UDP socket with handle %i on port %u\n", handle, port);
		Close();
		return false;
	}

	socketPort = port;

	Logger::Logf("Opened UDP socket on port %hu with handle %i\n", socketPort, handle);

	if (!blocking)
	{
		// Set socket to non-blocking mode
		#if defined(PLATFORM_WINDOWS)
			DWORD nonBlocking = 1;
			if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
			{
				Logger::LogErrorf("Could not set socket with handle %i to non-blocking IO\n", handle);
				return false;
			}
		#else
			int nonBlocking = 1;
			if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
			{
				Logger::LogErrorf("Could not set socket with handle %i to non-blocking IO\n", handle);
				return false;
			}
		#endif
	}

	// Enable UDP broadcast
	int broadcast = 1;
	if (setsockopt(handle, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast, sizeof broadcast) == -1)
	{
		Logger::LogErrorf("Could not set socket with handle %i to broadcast mode\n", handle);
		return false;
	}

	return true;
}

void UDPSocket::Close()
{
	if (IsOpen())
	{
		Logger::Logf("Closing socket with handle %i on port %u\n", handle, socketPort);

		#if defined(PLATFORM_WINDOWS)
			closesocket(handle);
		#else
			close(handle);
		#endif

		handle = 0;
		socketPort = 0;
	}
}

bool UDPSocket::IsOpen() const
{
	return handle != 0;
}

bool UDPSocket::Send(const IPAddress &destination, const void *data, int size)
{
	if (handle == 0 || size <= 0)
	{
		return false;
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination.GetAddress());
	address.sin_port = htons(destination.GetPort());

	int sent_bytes = sendto(handle, (const char*)data, size, 0, (sockaddr*)&address, sizeof(sockaddr_in));

	return sent_bytes == size;
}

int UDPSocket::Receive(IPAddress &sender, void *data, int size) const
{
	if (handle == 0 || size <= 0)
	{
		return 0;
	}	

	#if defined(PLATFORM_WINDOWS)
		typedef int socklen_t;
	#endif

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int received_bytes = recvfrom(handle, (char*)data, size, 0, (sockaddr*)&from, &fromLength);

	if (received_bytes <= 0)
	{
		return 0;
	}

	unsigned int address = ntohl(from.sin_addr.s_addr);
	unsigned int port = ntohs(from.sin_port);

	sender = IPAddress(address, port);

	return received_bytes;
}

bool UDPSocket::InitializeSocketLayer()
{
	if (enet_initialize() != 0)
	{
		Logger::LogErrorf("An error occurred while initializing Enet");
	}

	// todo - how does atexit work?
	atexit(enet_deinitialize);

	return true;
}

void UDPSocket::ShutdownSocketLayer()
{
	#if defined(PLATFORM_WINDOWS)
		WSACleanup();
	#endif
}

}
