#pragma once

#include "objects/Vehicle.hpp"
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
	Vehicle vehicle; // The most recent vehicle state from the server

	Vehicle displayVehicle; // The interpolated vehicle
	Vehicle lastVehicle; // The second-to-last vehicle state from the server
	float currentSmoothing;
protected:
private:
};

}
