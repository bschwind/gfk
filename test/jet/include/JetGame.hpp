#pragma once

#include "objects/Jet.hpp"
#include "JetCamera.hpp"
#include "network/RemoteConnection.hpp"
#include <GFK/Game.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>
#include <GFK/VR/VRCamera.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <enet/enet.h>

using namespace gfk;

namespace jetGame
{

class JetGame : public Game
{
public:
	JetGame(const std::string &title, int width, int height);
	~JetGame();

	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(const gfk::GameTime &gameTime);
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
	void EyeRenderFunction(const gfk::GameTime &gameTime, float interpolationFactor);
	void ResizeWindow(int width, int height);

	void ConnectToServer(const std::string &address, unsigned short port);
private:
	void UpdateNetwork(const gfk::GameTime &gameTime);
	void UpdateGame(const gfk::GameTime &gameTime);
	void SendStateToServer(const gfk::GameTime &gameTime);
	void HandleGamePacket(NetworkBuffer &netBuffer, unsigned char protocol);
	void DisconnectFromServer();
	unsigned long long int networkCounter;
	int networkSendsPerSecond;
	unsigned long long int updateCounter;
	PrimitiveBatch3D primBatch;
	JetCamera camera;
	VRCamera vrCam;
	Mesh mesh;
	ENetHost *client;
	ENetPeer *serverConnection;
	NetworkBuffer netBuffer;

	Jet jet;
};

}
