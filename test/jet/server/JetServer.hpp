#pragma once

#include "network/RemoteConnection.hpp"
#include <GFK/ConsoleGame.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
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
protected:
	void LoadContent();
	void Update(const gfk::GameTime &gameTime);
private:
	void UpdateNetwork(const gfk::GameTime &gameTime);
	void UpdateGame(const gfk::GameTime &gameTime);
	void SendStateToPlayers(const gfk::GameTime &gameTime);
	void HandleGamePacket(NetworkBuffer &netBuffer, unsigned char protocol);
	int networkCounter;
	int networkSendsPerSecond;
	int updateCounter;
	ENetHost *server;
	NetworkBuffer netBuffer;
};

}
