#pragma once

#include "network/RemoteConnection.hpp"
#include "network/PacketHandler.hpp"
#include <GFK/ConsoleGame.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <map>

using namespace gfk;

namespace jetGame
{

class JetServer : public ConsoleGame, public PacketHandler
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
	virtual void HandlePacket(NetworkBuffer &netBuffer, const IPAddress &sender, unsigned char protocol);

	int networkCounter;
	int networkSendsPerSecond;
	int updateCounter;
	UDPSocket socket;
	NetworkBuffer netBuffer;
	std::map<std::string, RemoteConnection> connections;
};

}
