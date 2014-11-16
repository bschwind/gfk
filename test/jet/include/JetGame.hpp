#pragma once

#include "objects/Jet.hpp"
#include "JetCamera.hpp"
#include "network/RemoteConnection.hpp"
#include <GFK/Game.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>

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
	void ResizeWindow(int width, int height);

	IPAddress ConnectToServer(const std::string &address, unsigned short port);
private:
	void UpdateNetwork(const gfk::GameTime &gameTime);
	void UpdateGame(const gfk::GameTime &gameTime);
	void SendStateToServer(const gfk::GameTime &gameTime);
	void HandleGamePacket(NetworkBuffer &netBuffer, const IPAddress &senderIP, unsigned char protocol);
	unsigned long long int networkCounter;
	int networkSendsPerSecond;
	unsigned long long int updateCounter;
	PrimitiveBatch3D primBatch;
	JetCamera camera;
	Mesh mesh;
	UDPSocket socket;
	NetworkBuffer netBuffer;
	RemoteConnection serverConnection;
	IPAddress serverAddress;

	Vector3 jetPos;

	Jet jet;
};

}
