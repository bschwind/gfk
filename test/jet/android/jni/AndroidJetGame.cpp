#include "AndroidJetGame.hpp"
#include "Packets.hpp"
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
netBuffer(4096),
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

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		Logger::LogError("Unable to create an ENet host");
	}

	ConnectToServer("192.168.24.53", 55777);

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

	DisconnectFromServer();
	enet_host_destroy(client);
}

void AndroidJetGame::DisconnectFromServer()
{
	ENetEvent event;
	enet_peer_disconnect(serverConnection, 0);

	while (enet_host_service(client, &event, 3000) > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				Logger::Log("Disconected from server\n");
				return;
		}
	}
}

void AndroidJetGame::Update(const gfk::GameTime &gameTime)
{
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToServer(gameTime);
}

void AndroidJetGame::UpdateNetwork(const gfk::GameTime &gameTime)
{
	ENetEvent event;
	unsigned char protocol;
	int serviceReturn = enet_host_service(client, &event, 0);

	while (serviceReturn > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
				Logger::Log("Someone connected\n");
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				netBuffer.PopulateData(event.packet->data, event.packet->dataLength);
				protocol = netBuffer.ReadUnsignedByte();
				HandleGamePacket(netBuffer, protocol);
				// todo - loop over all packets, not just the first one
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				Logger::Log("Someone disconnected\n");
				break;
			case ENET_EVENT_TYPE_NONE:
				Logger::Log("Nothing happened...");
				break;
			default:
				break;
		}

		serviceReturn = enet_host_service(client, &event, 0);
	}

	netBuffer.Reset();
}

void AndroidJetGame::HandleGamePacket(NetworkBuffer &netBuffer, unsigned char protocol)
{
	if (protocol == Packets::MOVEMENT)
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

void AndroidJetGame::ConnectToServer(const std::string &hostName, unsigned short port)
{
	ENetAddress address;
	ENetEvent event;
	enet_address_set_host(&address, hostName.c_str());
	address.port = port;

	serverConnection = enet_host_connect(client, &address, 2, 0); // 0 is for initial data

	if (serverConnection == NULL)
	{
		Logger::LogError("No network peers available\n");
	}

	if (enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		Logger::Log("Connected to server successfully!\n");
	}
	else
	{
		enet_peer_reset(serverConnection);
		Logger::LogError("Unable to connect to server");
	}
}

}
