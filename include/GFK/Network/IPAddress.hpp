#pragma once

#include <string>
#include <functional>

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
	static std::string GetBroadcastAddress();
protected:
private:
	unsigned int address;
	unsigned short port;
};

// The below operators and hash functions are needed to be able
// to insert IPAddress objects into an unordered_set

inline bool operator== (IPAddress const& lhs, IPAddress const& rhs)
{
	return (lhs.GetAddress() == rhs.GetAddress())
		&& (lhs.GetPort() == rhs.GetPort());
}

}

namespace std
{
	template <>
	struct hash<gfk::IPAddress>
	{
		size_t operator()(gfk::IPAddress const &x) const
		{
			return ((51 + std::hash<unsigned int>()(x.GetAddress())) * 51
				+ std::hash<unsigned short>()(x.GetPort())
			);
		}
	};
}
