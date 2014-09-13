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
	isFixedTimeStep = false;
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

	socket.Bind(55778);
	serverAddress = ConnectToServer("192.168.1.255", 55777);
	Logger::Logf("Server destination is %s\n", serverAddress.GetIPV4String().c_str());

	Device.SetClearColor(Color::Black);
}

void AndroidJetGame::LoadContent()
{
	Logger::Logf("load content()!");
}

void AndroidJetGame::UnloadContent()
{
	Logger::Log("unload content()!");

	serverConnection.WritePacket(DisconnectPacket());
	serverConnection.SendPackets(socket);

	socket.Close();
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

IPAddress AndroidJetGame::ConnectToServer(const std::string &address, unsigned short port)
{
	IPAddress destination;
	IPAddress::FromIPV4String(address, port, destination);

	serverConnection.clientType = ClientType::SERVER;
	serverConnection.address = destination;

	serverConnection.WritePacket(NewAndroidClientPacket(24));
	serverConnection.SendPackets(socket);

	double sentTime = GameTime::GetSystemTime();

	while (true)
	{
		int byteReadCount = socket.Receive(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

		if (!byteReadCount)
		{
			if (GameTime::GetSystemTime() - sentTime > 1.0)
			{
				std::cout << destination.GetIPV4String() << " took too long to respond" << std::endl;
				return destination;
			}
			continue;
		}

		break;
	}

	return destination;
}

}
