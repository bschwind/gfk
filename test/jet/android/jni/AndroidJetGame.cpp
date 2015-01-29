#include "AndroidJetGame.hpp"
#include "network/Packet.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/System/Logger.hpp>
#include <sstream>
#include <cmath>

using namespace gfk;

namespace jetGame
{

float jetX, jetY, jetZ;

AndroidJetGame::AndroidJetGame() :
Game(),
networkCounter(0),
networkSendsPerSecond(10),
netHelper(NetworkHelper::ConnectionType::Client)
{
	Logger::Log("Jet Game Constructor!");
	isFixedTimeStep = true;
	targetUpdateFramesPerSecond = 60;
}

AndroidJetGame::~AndroidJetGame()
{
	Logger::Log("Jet Game Destructor!");
}

void AndroidJetGame::Initialize()
{
	Logger::Log("initialize()!");
	gfk::Game::Initialize();
	primBatch.Initialize();

	netHelper.ConnectToServer("192.168.24.53", 55777);
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, gameTime);
		}
	);

	Device.SetClearColor(Color::Black);
}

void AndroidJetGame::LoadContent()
{
	gfk::Game::LoadContent();
	Logger::Logf("load content()!");
}

void AndroidJetGame::UnloadContent()
{
	gfk::Game::UnloadContent();
	Logger::Log("unload content()!");

	netHelper.DisconnectFromServer();
}

void AndroidJetGame::Update(const gfk::GameTime &gameTime)
{
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToServer(gameTime);
}

void AndroidJetGame::UpdateNetwork(const gfk::GameTime &gameTime)
{
	netHelper.Receive(gameTime);
}

void AndroidJetGame::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, const gfk::GameTime &gameTime)
{
	if (protocol == Packet::JET_INPUT_RES)
	{
		jetX = netBuffer.ReadFloat32();
		jetY = netBuffer.ReadFloat32();
		jetZ = netBuffer.ReadFloat32();
	}
}

void AndroidJetGame::UpdateGame(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;
	double totalTime = gameTime.TotalGameTime;

	cam.SetPos(Vector3(0, 1, 0));
}

void AndroidJetGame::SendStateToServer(const gfk::GameTime &gameTime)
{
	int iterCutoff = targetUpdateFramesPerSecond / networkSendsPerSecond;

	if (networkCounter >= iterCutoff)
	{
		netHelper.Send();
		networkCounter = 1;
	}
	else
	{
		networkCounter++;
	}
}

void AndroidJetGame::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	Color color = Color::Gray;
	color.A = 0.3f;

	primBatch.Begin(PrimitiveType::LineList, cam);
	primBatch.DrawXZGrid(-20, -20, 20, 20, color);
	primBatch.DrawLine(Vector3(jetX, 0, jetZ), Vector3(jetX, jetY, jetZ), Color::Red, Color::Red);
	primBatch.End();

	primBatch.Begin(PrimitiveType::TriangleList, cam);
	primBatch.FillSphere(Vector3(jetX, jetY, jetZ), 1, 10, 10, Color::Red);
	primBatch.End();

	Device.SwapBuffers();
}

void AndroidJetGame::ResizeWindow(int width, int height)
{
	gfk::Game::ResizeWindow(width, height);
	cam.SetScreenWidth(width);
	cam.SetScreenHeight(height);
}

}
