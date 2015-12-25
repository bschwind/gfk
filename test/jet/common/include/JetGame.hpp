#pragma once

#include "objects/Jet.hpp"
#include "objects/ClientData.hpp"
#include "objects/GameInput.hpp"
#include "JetCamera.hpp"
#include "network/Packet.hpp"
#include "network/JetClient.hpp"
#include <GFK/Game.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>
#include <GFK/VR/VRCamera.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/Network/NetworkBuffer.hpp>
#include <enet/enet.h>
#include <deque>

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
	void Update(const gfk::GameTime &gameTime) override;
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
	void EyeRenderFunction(const gfk::GameTime &gameTime, float interpolationFactor);
	void ResizeWindow(int width, int height);
private:
	void UpdateNetwork(const gfk::GameTime &gameTime);
	void UpdateGame(const gfk::GameTime &gameTime);
	GameInput GetCurrentInput(const gfk::GameTime &gameTime);
	void SendStateToServer(const gfk::GameTime &gameTime);
	unsigned long long int networkCounter;
	int networkSendsPerSecond;
	unsigned long long int updateCounter;
	PrimitiveBatch3D primBatch;
	JetCamera camera;
	VRCamera vrCam;
	Mesh mesh;
	JetClient jetClient;

	std::deque<GameInput> inputs;
	unsigned int inputSequenceNumber;
};

}
