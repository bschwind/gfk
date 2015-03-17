#include "objects/ClientData.hpp"
#include <iostream>

namespace jetGame
{

ClientData::ClientData() :
id(0),
clientType(0),
lastInputSequenceNumber(0),
outbox(0),
currentSmoothing(0.0f)
{

}

ClientData::ClientData(unsigned int outgoingBufferSize) :
id(0),
clientType(0),
lastInputSequenceNumber(0),
outbox(outgoingBufferSize),
currentSmoothing(0.0f)
{

}

ClientData::~ClientData()
{

}

}
