#include "include/JetGame.hpp"
#include "include/Packets.hpp"
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
camera(),
mesh("assets/Airplane F18 N120712.3DS"),
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

	// Exit Conditions
	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		netBuffer.WriteUnsignedInt32(Packets::applicationID);
		netBuffer.WriteUnsignedInt32(0); // sequence
		netBuffer.WriteUnsignedInt32(0); // ack
		netBuffer.WriteUnsignedInt32(32); // ack bitfield
		netBuffer.WriteUnsignedByte(1); // num packets
		netBuffer.WriteUnsignedByte(Packets::DISCONNECT);

		gfk::Game::Exit();
	}
	else
	{
		// Update Network
		netBuffer.WriteUnsignedInt32(Packets::applicationID);
		netBuffer.WriteUnsignedInt32(0); // sequence
		netBuffer.WriteUnsignedInt32(0); // ack
		netBuffer.WriteUnsignedInt32(0); // ack bitfield
		netBuffer.WriteUnsignedByte(1); // num packets
		netBuffer.WriteUnsignedByte(Packets::MOVEMENT);
		netBuffer.WriteFloat32(jet.GetPosition().X);
		netBuffer.WriteFloat32(jet.GetPosition().Y);
		netBuffer.WriteFloat32(jet.GetPosition().Z);
	}

	socket.Send(serverAddress, netBuffer.GetDataBuffer(), netBuffer.GetBufferCount());

	netBuffer.Reset();
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

	unsigned int sequence = 0;;
	unsigned int ack = 0;
	unsigned int ackBitfield = 0;

	NetworkBuffer netBuffer;
	netBuffer.WriteUnsignedInt32(Packets::applicationID);
	netBuffer.WriteUnsignedInt32(sequence);
	netBuffer.WriteUnsignedInt32(ack);
	netBuffer.WriteUnsignedInt32(ackBitfield);
	netBuffer.WriteUnsignedByte(1);
	netBuffer.WriteUnsignedByte(Packets::NEW_DESKTOP_CLIENT);

	socket.Send(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCount());

	double sentTime = GameTime::GetSystemTime();

	while (true)
	{
		int byteReadCount = socket.Receive(destination, netBuffer.GetDataBuffer(), netBuffer.GetBufferCapacity());

		if (!byteReadCount)
		{
			if (GameTime::GetSystemTime() - sentTime > 3.3)
			{
				std::cout << (GameTime::GetSystemTime() - sentTime) << std::endl;

				std::cout << destination.GetIPV4String() << " took too long to respond, trying broadcast address" << std::endl;

				std::string broadcastAddressToTry = "192.168.1.255" + std::to_string(port);
				if (destination.GetIPV4String().compare(broadcastAddressToTry) == 0)
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
