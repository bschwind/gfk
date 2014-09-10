#pragma once

#include <string>

namespace gfk
{

class IPAddress
{
	
public:
	IPAddress();
	IPAddress(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port);
	IPAddress(unsigned int address, unsigned short port);
	~IPAddress();

	unsigned int GetAddress() const;
	unsigned char GetA() const;
	unsigned char GetB() const;
	unsigned char GetC() const;
	unsigned char GetD() const;
	unsigned short GetPort() const;
	std::string GetIPV4String() const;

	static int FromIPV4String(std::string address, unsigned short port, IPAddress &IPAddress);
protected:
private:
	unsigned int address;
	unsigned short port;
};

}
