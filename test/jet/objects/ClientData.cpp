#include "objects/ClientData.hpp"
#include <iostream>

namespace jetGame
{

ClientData::ClientData() :
outbox(0)
{

}

ClientData::ClientData(unsigned int outgoingBufferSize) :
outbox(outgoingBufferSize)
{

}

ClientData::~ClientData()
{

}

}
