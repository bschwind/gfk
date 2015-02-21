#include "AndroidJetGame.hpp"
#include "network/Packet.hpp"
#include "objects/Jet.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/System/Logger.hpp>
#include <sstream>
#include <cmath>

using namespace gfk;

namespace jetGame
{

AndroidJetGame::AndroidJetGame() :
Game(),
networkCounter(0),
networkSendsPerSecond(10)
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

	jetClient.ConnectToServer("192.168.24.53", 55777, ClientType::GFK_ANDROID);

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
	jetClient.DisconnectFromServer();
}

void AndroidJetGame::Update(const gfk::GameTime &gameTime)
{
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToServer(gameTime);
}

void AndroidJetGame::UpdateNetwork(const gfk::GameTime &gameTime)
{
	jetClient.ProcessIncomingPackets(gameTime);
}

void AndroidJetGame::UpdateGame(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;
	double totalTime = gameTime.TotalGameTime;
}

void AndroidJetGame::SendStateToServer(const gfk::GameTime &gameTime)
{
	int iterCutoff = targetUpdateFramesPerSecond / networkSendsPerSecond;

	if (networkCounter >= iterCutoff)
	{
		jetClient.SendOutgoingPackets();
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
	primBatch.DrawXZGrid(-200, -200, 200, 200, color);
	primBatch.End();

	for (auto player : jetClient.players)
	{
		Matrix world = player.second.jet.GetTransform();
		float jetX = player.second.jet.GetPosition().X;
		float jetY = player.second.jet.GetPosition().Y;
		float jetZ = player.second.jet.GetPosition().Z;

		primBatch.Begin(PrimitiveType::LineList, cam);
		primBatch.DrawLine(Vector3(jetX, 0, jetZ), Vector3(jetX, jetY, jetZ), Color::Red, Color::Red);
		primBatch.End();

		primBatch.Begin(PrimitiveType::TriangleList, cam, world);
		primBatch.FillTriangle(Vector3(-0.5f, 0, 0), Vector3(0, 0, -1), Vector3(0.5f, 0, 0), Color::Red, Color::Red, Color::Red);
		primBatch.FillTriangle(Vector3(0, 0, 0), Vector3(0, 0.5f, 0), Vector3(0, 0, -1), Color::Blue, Color::Blue, Color::Blue);
		primBatch.End();
	}

	Device.SwapBuffers();
}

void AndroidJetGame::ResizeWindow(int width, int height)
{
	gfk::Game::ResizeWindow(width, height);
	cam.SetScreenWidth(width);
	cam.SetScreenHeight(height);
}

}
