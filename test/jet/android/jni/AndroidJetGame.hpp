#pragma once

#include "TopDownCamera.hpp"
#include "network/NetworkHelper.hpp"
#include "network/JetClient.hpp"
#include "objects/ClientData.hpp"
#include <GFK/Game.hpp>
#include <GFK/Graphics/Mesh.hpp>
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
	AndroidJetGame(android_app *app);
	~AndroidJetGame();

	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(const gfk::GameTime &gameTime);
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
	void ResizeWindow(int width, int height);
private:
	void UpdateNetwork(const gfk::GameTime &gameTime);
	void UpdateGame(const gfk::GameTime &gameTime);
	void SendStateToServer(const gfk::GameTime &gameTime);

	TopDownCamera cam;
	PrimitiveBatch3D primBatch;
	unsigned long long int networkCounter;
	int networkSendsPerSecond;
	Mesh mesh;
	JetClient jetClient;
};

}
