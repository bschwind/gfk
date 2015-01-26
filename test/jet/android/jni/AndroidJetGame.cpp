#include "AndroidJetGame.hpp"
#include "Packets.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/System/Logger.hpp>
#include <sstream>
#include <cmath>

using namespace gfk;

namespace jetGame
{

AndroidJetGame::AndroidJetGame() :
Game(),
netBuffer(4096)
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

	ConnectToServer("127.0.0.1", 55777);

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
	IPAddress sender;

	while (true)
	{
		int numBytesRead = socket.Receive(sender, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

		if (numBytesRead > 0)
		{
			unsigned int applicationID = netBuffer.ReadUnsignedInt32();
			unsigned int sequence = netBuffer.ReadUnsignedInt32();
			unsigned int ack = netBuffer.ReadUnsignedInt32();
			unsigned int ackBitfield = netBuffer.ReadUnsignedInt32();
			unsigned int numPackets = netBuffer.ReadUnsignedByte();

			if (applicationID == Packets::applicationID)
			{
				std::string ipAddress = sender.GetIPV4String();
				// std::cout << "Received packet from " << ipAddress << std::endl;
				unsigned char protocol = netBuffer.ReadUnsignedByte();
			}
		}
		else
		{
			break;
		}

		netBuffer.Reset();
	}

	netBuffer.Reset();

	float dt = gameTime.ElapsedGameTime;
	double totalTime = gameTime.TotalGameTime;

	cam.SetPos(Vector3(0, 10, 0));
}

void AndroidJetGame::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	Color color = Color::Gray;
	color.A = 0.3f;

	primBatch.Begin(PrimitiveType::LineList, cam);
	primBatch.DrawXZGrid(-200, -200, 200, 200, color);
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
