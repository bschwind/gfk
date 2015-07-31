#pragma once

#include <GFK/Network/NetworkBuffer.hpp>
#include <GFK/System/GameTime.hpp>
#include "network/NetworkHelper.hpp"
#include "network/ClientType.hpp"
#include "objects/ClientData.hpp"
#include <map>

using namespace gfk;

namespace jetGame
{

class JetClient
{
public:
	JetClient();
	~JetClient();

	void ConnectToServer(const std::string &hostName, unsigned short port, unsigned char clientType);
	void DisconnectFromServer();
	void ProcessIncomingPackets(const gfk::GameTime &gameTime);
	void WritePacket(const Packet &packet, bool reliable);
	void SendOutgoingPackets();
	void Update(const gfk::GameTime &gameTime);
	ClientData* GetLocalClient();
	void PrintGameInfo();

	std::map<unsigned short, ClientData> players;
	unsigned short localPlayerId;

	// todo - this is pretty hacky, the input gathering
	//        should be built into JetClient instead of
	//        this variable being used externally
	bool receivedNewInput;
private:
	void HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime);
	
	NetworkHelper netHelper;
};

}
