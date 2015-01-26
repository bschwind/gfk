#pragma once

#include "TopDownCamera.hpp"
#include <GFK/Game.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <enet/enet.h>

using namespace gfk;

namespace jetGame
{

class AndroidJetGame : public Game
{
public:
	AndroidJetGame();
	~AndroidJetGame();

	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(const gfk::GameTime &gameTime);
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
	void ResizeWindow(int width, int height);
private:
	TopDownCamera cam;
	PrimitiveBatch3D primBatch;
	UDPSocket socket;
	NetworkBuffer netBuffer;
	ENetHost *client;
	ENetPeer *serverConnection;
	unsigned long long int networkCounter;
	int networkSendsPerSecond;

	void ConnectToServer(const std::string &address, unsigned short port);
	void UpdateNetwork(const gfk::GameTime &gameTime);
	void HandleGamePacket(NetworkBuffer &netBuffer, unsigned char protocol);
	void UpdateGame(const gfk::GameTime &gameTime);
	void SendStateToServer(const gfk::GameTime &gameTime);
	void DisconnectFromServer();
};

}
