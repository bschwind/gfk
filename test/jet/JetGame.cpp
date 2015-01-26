#include "include/JetGame.hpp"
#include "include/Packets.hpp"
#include "network/Packet.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/Input/Keyboard.hpp>
#include <GFK/Input/Mouse.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/System/Logger.hpp>
#include <iostream>
#include <cmath>

#include <GFK/Math/Quaternion.hpp>

namespace jetGame
{

JetGame::JetGame(const std::string &title, int width, int height) :
Game(title, width, height),
networkCounter(0),
networkSendsPerSecond(10),
updateCounter(0),
camera(),
vrCam(),
mesh("assets/f18Hornet.3DS"),
netBuffer(4096),
jet(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0))
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

	auto renderFunction = [this](gfk::GameTime gameTime, float interpolationFactor)
	{
		EyeRenderFunction(gameTime, interpolationFactor);
	};
	vrCam.Initialize(renderFunction);

	client = enet_host_create(NULL, 1, 2, 0, 0);

	if (client == NULL)
	{
		Logger::LogError("Unable to create an ENet host");
	}

	ConnectToServer("127.0.0.1", 55777);

	Device.SetClearColor(Color::Black);

	Mouse::SetPos(Vector2(0, 0));
}

void JetGame::LoadContent()
{
	gfk::Game::LoadContent();
}

void JetGame::UnloadContent()
{
	gfk::Game::UnloadContent();
	DisconnectFromServer();
	enet_host_destroy(client);
}

void JetGame::DisconnectFromServer()
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
	ENetEvent event;
	int serviceReturn = enet_host_service(client, &event, 0);

	while (serviceReturn > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
				Logger::Log("Someone connected\n");
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				Logger::Log("Got some data\n");
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
}

void JetGame::UpdateGame(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;

	// Update Input
	Vector2 diff = Mouse::GetPos();

	// This is a dirty hack for the way the GLFW cursor "jumps" when
	// you first move it. Will likely be fixed in a later release
	if (firstMouseMove && (fabs(diff.X) > 0 || fabs(diff.Y) > 0))
	{
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

	Quaternion cameraRotation = vrCam.GetRotation();// * Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), MathHelper::ToRadians(90.0f));

	jet.Update(throttle, diff.X, diff.Y, 0.0f, thrusterEnabled, gameTime);

	camera.Update(dt, Vector3::Transform(Vector3(0, 0, -1), cameraRotation),
		Vector3::Transform(Vector3(0, 1, 0), cameraRotation),
		Vector3::Transform(Vector3(1, 0, 0), cameraRotation));

	Vector3 offset = Vector3(0, 5, 10);
	offset = Vector3::Zero;

	camera.SetPos(offset + vrCam.GetPosition());

	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		gfk::Game::Exit();
	}

	if (Keyboard::IsKeyDown(Keys::Space))
	{
		vrCam.Recenter();
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
		MovementPacket(x, y, z).WriteToBuffer(netBuffer);

		ENetPacket *packet = enet_packet_create(netBuffer.GetDataBuffer(), netBuffer.GetBufferCount(), 0);

		enet_peer_send(serverConnection, 0, packet);
		enet_host_flush(client);

		networkCounter = 1;
		netBuffer.Reset();
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

	primBatch.End();

	primBatch.Begin(PrimitiveType::TriangleList, camera);
	primBatch.FillSphere(vrCam.GetTrackingCameraPosition(), 0.1f, 10, 10, Color::Red);

	primBatch.End();

	Matrix world = jet.GetTransform() * Matrix::CreateRotationY(MathHelper::ToRadians(90.0f));
	primBatch.Begin(PrimitiveType::TriangleList, camera, world);
	primBatch.DrawMesh(mesh);
	primBatch.End();

	Device.SwapBuffers();

	vrCam.Render(gameTime, interpolationFactor);
}

void JetGame::EyeRenderFunction(const gfk::GameTime &gameTime, float interpolationFactor)
{

}

void JetGame::ResizeWindow(int width, int height)
{
	gfk::Game::ResizeWindow(width, height);

	camera.SetScreenWidth(width);
	camera.SetScreenHeight(height);
}

void JetGame::ConnectToServer(const std::string &hostName, unsigned short port)
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
