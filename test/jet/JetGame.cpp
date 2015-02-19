#include "include/JetGame.hpp"
#include "network/Packet.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/Input/Keyboard.hpp>
#include <GFK/Input/Mouse.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <GFK/System/Logger.hpp>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

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
netHelper(NetworkHelper::ConnectionType::Client)
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

	netHelper.ConnectToServer("127.0.0.1", 55777);
	netHelper.RegisterReceiveHandler([this](gfk::NetworkBuffer &networkBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
		{
			HandleGamePacket(networkBuffer, protocol, clientData, gameTime);
		}
	);

	netHelper.WritePacket(NewDesktopClientPacketReq());
	netHelper.Send();

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

	netHelper.WritePacket(DisconnectPacketReq());
	netHelper.Send();

	// HACK: Give the disconnect packet time to reach the server
	// before cutting off the connection. Get a more graceful solution later.
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	netHelper.DisconnectFromServer();
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
	netHelper.Receive(gameTime);
}

void JetGame::HandleGamePacket(NetworkBuffer &netBuffer, unsigned short protocol, ClientData &clientData, const gfk::GameTime &gameTime)
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
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Android user joined with id %hu\n", playerId);
		players[playerId] = ClientData();
	}
	else if (protocol == Packet::CLIENT_ID_RES)
	{
		localPlayerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Got ID from server: %hu\n", localPlayerId);
	}
	else if (protocol == Packet::DISCONNECT_RES)
	{
		unsigned short playerId = netBuffer.ReadUnsignedInt16();
		Logger::Logf("Player %hu disconnected\n", playerId);
		players.erase(playerId);
	}
}

unsigned int updateCount = 0;

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

	jetInputPacket.throttleAmt = throttle;
	jetInputPacket.rollInput = diff.X;
	jetInputPacket.pitchInput = diff.Y;
	jetInputPacket.yawInput = 0.0f;
	jetInputPacket.thrusterEnabled = thrusterEnabled ? 1 : 0;
	jetInputPacket.updateCount = updateCount;
	netHelper.WritePacket(jetInputPacket);

	camera.Update(dt, Vector3::Transform(Vector3(0, 0, -1), cameraRotation),
		Vector3::Transform(Vector3(0, 1, 0), cameraRotation),
		Vector3::Transform(Vector3(1, 0, 0), cameraRotation));

	camera.SetPos(Vector3(0, 10, 10));

	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		gfk::Game::Exit();
	}

	if (Keyboard::IsKeyDown(Keys::Space))
	{
		vrCam.Recenter();
	}

	updateCount++;
}

void JetGame::SendStateToServer(const gfk::GameTime &gameTime)
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

	for (auto player : players)
	{
		Matrix world = player.second.jet.GetTransform() * Matrix::CreateRotationY(MathHelper::ToRadians(90.0f));
		primBatch.Begin(PrimitiveType::TriangleList, camera, world);
		primBatch.DrawMesh(mesh);
		primBatch.End();
	}

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

}
