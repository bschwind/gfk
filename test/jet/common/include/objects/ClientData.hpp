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
	unsigned int lastInputSequenceNumber;
	Outbox outbox;
	Jet jet; // The most recent jet state from the server

	Jet displayJet; // The interpolated jet
	Jet lastJet; // The second-to-last jet state from the server
	float currentSmoothing;
protected:
private:
};

}
