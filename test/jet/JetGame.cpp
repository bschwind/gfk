#include "include/JetGame.hpp"
#include "include/Packets.hpp"
#include "network/Packet.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/Input/Keyboard.hpp>
#include <GFK/Input/Mouse.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <iostream>
#include <cmath>

#include <GFK/Math/MathHelper.hpp>

namespace jetGame
{

JetGame::JetGame(const std::string &title, int width, int height) :
Game(title, width, height),
networkCounter(0),
networkSendsPerSecond(10),
updateCounter(0),
camera(),
mesh("assets/f18Hornet.3DS"),
netBuffer(4096),
jet(Vector3(0, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0))
{
	isFixedTimeStep = true;
	targetUpdateFramesPerSecond = 60;

	camera.SetScreenWidth(width);
	camera.SetScreenHeight(height);
}

JetGame::~JetGame()
{
	
}

void JetGame::Initialize()
{
	gfk::Game::Initialize();
	primBatch.Initialize();

	socket.Bind(55778);
	serverAddress = ConnectToServer("127.0.0.1", 55777);
	std::cout << "Server destination is " << serverAddress.GetIPV4String() << std::endl;

	Device.SetClearColor(Color::Black);

	Mouse::SetPos(Vector2(0, 0));
}

void JetGame::LoadContent()
{

}

void JetGame::UnloadContent()
{

}

bool firstMouseMove = true;

void JetGame::Update(const gfk::GameTime &gameTime)
{
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToServer(gameTime);

	updateCounter++;
}

void JetGame::UpdateNetwork(const gfk::GameTime &gameTime)
{

}

void JetGame::UpdateGame(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;

	// Update Input
	Vector2 diff = Mouse::GetPos();

	// This is a dirty hack for the way the GLFW cursor "jumps" when
	// you first move it. Will likely be fixed in a later release
	if (firstMouseMove && (fabs(diff.X) > 0 || fabs(diff.Y) > 0)) {
		diff.X = 0;
		diff.Y = 0;

		firstMouseMove = false;
	}

	Mouse::SetPos(Vector2(0,0));

	float throttle = 0.0f;
	bool thrusterEnabled = false;

	if (Keyboard::IsKeyDown(Keys::W))
	{
		throttle = 1.0f;
	}
	else if (Keyboard::IsKeyDown(Keys::S))
	{
		throttle = -1.0f;
	}

	if (Keyboard::IsKeyDown(Keys::LeftShift))
	{
		thrusterEnabled = true;
	}

	jet.Update(throttle, diff.X, diff.Y, 0.0f, thrusterEnabled, gameTime);
	camera.Update(dt, jet.GetForward(), jet.GetUp(), jet.GetRight());
	camera.SetPos(jet.GetPosition() - jet.GetForward() * 50 + jet.GetUp() * 8);

	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		// Send disconnect packet
		serverConnection.WritePacket(DisconnectPacket());
		serverConnection.SendPackets(socket);

		gfk::Game::Exit();
	}
}

void JetGame::SendStateToServer(const gfk::GameTime &gameTime)
{
	int iterCutoff = targetUpdateFramesPerSecond / networkSendsPerSecond;

	if (networkCounter >= iterCutoff)
	{
		std::cout << "network send! " << gameTime.TotalGameTime << std::endl;

		// Send movement packet
		float x = jet.GetPosition().X;
		float y = jet.GetPosition().Y;
		float z = jet.GetPosition().Z;
		serverConnection.WritePacket(MovementPacket(x, y, z));
		serverConnection.SendPackets(socket);

		networkCounter = 1;
	}
	else
	{
		networkCounter++;
	}
}

void JetGame::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	// Draw world grid and axis references
	primBatch.Begin(PrimitiveType::LineList, camera);
	Color color = Color::Gray;
	color.A = 0.3f;
	primBatch.DrawXZGrid(-200, -200, 200, 200, color);
	primBatch.DrawLine(Vector3::Zero, Vector3::UnitX, Color::Red, Color::Red);
	primBatch.DrawLine(Vector3::Zero, Vector3::UnitY, Color::Green, Color::Green);
	primBatch.DrawLine(Vector3::Zero, Vector3::UnitZ, Color::Blue, Color::Blue);

	primBatch.DrawLine(jet.GetPosition(), jet.GetPosition() + jet.GetForward() * 15, Color::Red, Color::Red);
	primBatch.DrawLine(jet.GetPosition(), jet.GetPosition() + jet.GetUp() * 15, Color::Green, Color::Green);
	primBatch.DrawLine(jet.GetPosition(), jet.GetPosition() + jet.GetRight() * 15, Color::Blue, Color::Blue);

	primBatch.End();

	primBatch.Begin(PrimitiveType::TriangleList, camera);
	primBatch.FillSphere(jet.GetPosition() + jet.GetForward() * 15, 2, 10, 10, Color::Red);
	primBatch.FillSphere(jet.GetPosition() + jet.GetUp() * 15, 2, 10, 10, Color::Green);
	primBatch.FillSphere(jet.GetPosition() + jet.GetRight() * 15, 2, 10, 10, Color::Blue);
	primBatch.End();

	Matrix world = jet.GetTransform();
	primBatch.Begin(PrimitiveType::TriangleList, camera, world);
	primBatch.DrawMesh(mesh);
	primBatch.End();

	Device.SwapBuffers();
}

void JetGame::ResizeWindow(int width, int height)
{
	gfk::Game::ResizeWindow(width, height);

	camera.SetScreenWidth(width);
	camera.SetScreenHeight(height);
}

IPAddress JetGame::ConnectToServer(const std::string &address, unsigned short port)
{
	IPAddress destination;
	IPAddress::FromIPV4String(address, port, destination);

	serverConnection.clientType = ClientType::SERVER;
	serverConnection.address = destination;

	serverConnection.WritePacket(NewDesktopClientPacket(24));
	serverConnection.SendPackets(socket);

	double sentTime = GameTime::GetSystemTime();

	while (true)
	{
		int byteReadCount = socket.Receive(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

		if (!byteReadCount)
		{
			if (GameTime::GetSystemTime() - sentTime > 1.0)
			{
				std::cout << (GameTime::GetSystemTime() - sentTime) << std::endl;

				std::cout << destination.GetIPV4String() << " took too long to respond, trying broadcast address" << std::endl;

				std::string broadcastAddressToTry = "192.168.1.255:" + std::to_string(port);
				if (destination.GetIPV4String().compare(broadcastAddressToTry) != 0)
				{
					return ConnectToServer("192.168.1.255", port);
				}

				return destination;
			}
			continue;
		}

		break;
	}

	return destination;
}

}
