#pragma once

#include "objects/Jet.hpp"

namespace jetGame
{

class ClientData
{
public:
	ClientData();
	~ClientData();

	unsigned short id;
	unsigned char clientType;
	Jet jet;
protected:
private:
};

}
