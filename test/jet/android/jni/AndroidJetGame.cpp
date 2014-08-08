#include "AndroidJetGame.hpp"
#include "Packets.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/System/Logger.hpp>
#include <cmath>

using namespace gfk;

namespace jetGame
{

AndroidJetGame::AndroidJetGame() :
Game()
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
	socket.Close();
}

void AndroidJetGame::Update(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;
	double totalTime = gameTime.TotalGameTime;
	Vector3 pos;

	pos.X = (float)sin(totalTime) * 3;
	pos.Y = 10;
	pos.Z = (float)cos(totalTime) * 3;

	cam.SetPos(pos);
}

void AndroidJetGame::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	primBatch.Begin(PrimitiveType::LineList, cam);
	
	Color color = Color::Gray;
	color.A = 0.3f;
	primBatch.DrawXZGrid(-200, -200, 200, 200, color);

	primBatch.DrawLine(Vector3(0, 0, 0), Vector3(2, 0, -2), Color::Red, Color::Red);
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

	unsigned int sequence = 0;
	unsigned int ack = 0;
	unsigned int ackBitfield = 0;

	NetworkBuffer netBuffer;
	netBuffer.WriteUnsignedInt32(Packets::applicationID);
	netBuffer.WriteUnsignedInt32(sequence);
	netBuffer.WriteUnsignedInt32(ack);
	netBuffer.WriteUnsignedInt32(ackBitfield);
	netBuffer.WriteUnsignedByte(Packets::NEW_ANDROID_CLIENT);
	socket.Send(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCount());

	double sentTime = GameTime::GetSystemTime();

	while (true)
	{
		int byteReadCount = socket.Receive(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

		if (!byteReadCount)
		{
			if (GameTime::GetSystemTime() - sentTime > 3.3)
			{
				Logger::Log("Server took too long to respond");
				return destination;
			}
			continue;
		}

		break;
	}

	return destination;
}

}
