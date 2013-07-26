#include <GFK/OSDetection.hpp>

#if defined(PLATFORM_WINDOWS)
	#include <winsock2.h>
	// This compiler directive tells the windows compiler to link to wsock32.lib
	#pragma comment( lib, "wsock32.lib" )
#elif defined(PLATFORM_MAC) || defined(PLATFORM_UNIX)
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
	#include <unistd.h>
#endif

namespace gfk
{

class UDPSocket
{
public:
	UDPSocket();
	~UDPSocket();
	bool Open(unsigned short port);
	void Close();
	bool IsOpen() const;
	//bool Send(const Address & destination, const void * data, int size);
	//int Receive(Address & sender, void * data, int size);

	static bool InitializeSocketLayer();
	static void ShutdownSocketLayer();
protected:
private:
	int handle;
	unsigned short socketPort;
	static bool socketsInitialized;
};

}
