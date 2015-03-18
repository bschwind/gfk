#pragma once

#include "objects/Jet.hpp"
#include "objects/ClientData.hpp"
#include "network/NetworkHelper.hpp"
#include <GFK/ConsoleGame.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>
#include <GFK/Network/NetDiscoveryServer.hpp>
#include <enet/enet.h>

using namespace gfk;

namespace jetGame
{

class JetServer : public ConsoleGame
{
public:
	JetServer();
	~JetServer();
	void Initialize();
	void UnloadContent();
	void PrintServerInfo();
protected:
	void LoadContent();
	void Update(const gfk::GameTime &gameTime);
private:
	void UpdateNetwork(const gfk::GameTime &gameTime);
	void UpdateGame(const gfk::GameTime &gameTime);
	void SendStateToPlayers(const gfk::GameTime &gameTime);
	void HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime);
	int networkCounter;
	int networkSendsPerSecond;
	int updateCounter;
	unsigned short playerIdCounter;
	NetworkHelper netHelper;
	NetDiscoveryServer netDiscoveryServer;
};

}
