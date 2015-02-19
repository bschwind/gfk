#pragma once

#include "objects/Jet.hpp"
#include "network/Outbox.hpp"
#include <GFK/Network/NetworkBuffer.hpp>

namespace jetGame
{

class ClientData
{
public:
	ClientData();
	ClientData(unsigned int outgoingBufferSize);
	~ClientData();

	unsigned short id;
	unsigned char clientType;
	Outbox outbox;
	Jet jet;
protected:
private:
};

}
