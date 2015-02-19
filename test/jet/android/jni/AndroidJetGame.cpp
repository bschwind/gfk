#include "AndroidJetGame.hpp"
#include "network/Packet.hpp"
#include "objects/Jet.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/System/Logger.hpp>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace gfk;

namespace jetGame
{

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
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, clientData, gameTime);
		}
	);

	netHelper.WritePacket(NewAndroidClientPacketReq());
	netHelper.Send();

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

	netHelper.WritePacket(DisconnectPacketReq());
	netHelper.Send();

	// Give the disconnect packet time to reach the server
	// before cutting off the connection
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

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

void AndroidJetGame::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
{
	if (protocol == Packet::JET_INPUT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		float jetX = netBuffer.ReadFloat32();
		float jetY = netBuffer.ReadFloat32();
		float jetZ = netBuffer.ReadFloat32();

		float jetRX = netBuffer.ReadFloat32();
		float jetRY = netBuffer.ReadFloat32();
		float jetRZ = netBuffer.ReadFloat32();
		float jetRW = netBuffer.ReadFloat32();

		if (players.find(playerId) != players.end())
		{
			ClientData &player = players[playerId];

			player.jet.SetPosition(Vector3(jetX, jetY, jetZ));
			player.jet.SetRotation(Quaternion(jetRX, jetRY, jetRZ, jetRW));
		}
	}
	else if (protocol == Packet::NEW_DESKTOP_CLIENT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Desktop user joined with id %hu\n", playerId);
		players[playerId] = ClientData();
	}
	else if (protocol == Packet::NEW_ANDROID_CLIENT_RES)
	{
		unsigned short playerID = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Android user joined with id %d\n", playerID);
		players[playerID] = ClientData();
	}
	else if (protocol == Packet::CLIENT_ID_RES)
	{
		localPlayerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Got ID from server: %hu\n", localPlayerId);
	}
	else if (protocol == Packet::DISCONNECT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Player %d disconnected\n", playerId);
		players.erase(playerId);
	}
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
	primBatch.DrawXZGrid(-200, -200, 200, 200, color);
	primBatch.End();

	for (auto player : players)
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
