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
inputSequenceNumber(0)
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

	jetClient.ConnectToServer("127.0.0.1", 55777, ClientType::DESKTOP);

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
	jetClient.DisconnectFromServer();
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
	jetClient.ProcessIncomingPackets(gameTime);

	ClientData *localClient = jetClient.GetLocalClient();

	if (localClient)
	{
		Jet &jet = localClient->jet;
		unsigned int lastInputSequenceNumber = jetClient.players[jetClient.localPlayerId].lastInputSequenceNumber;

		if (inputs.size() > 0 && jetClient.receivedNewInput)
		{
			jetClient.receivedNewInput = false;

			// Flush out all inputs already acked
			GameInput &frontInput = inputs.front();
			while (inputs.size() > 0 && frontInput.sequenceNumber <= lastInputSequenceNumber)
			{
				inputs.pop_front();
				if (inputs.size() > 0)
				{
					frontInput = inputs.front();
				}
			}

			if (inputs.size() > 0)
			{
				// Apply the rest of the unacknowledged inputs,
				// starting from the last known good server state
				for (GameInput &input : inputs)
				{
					jet.Update(input, gameTime);
				}
			}
		}
	}
}

void JetGame::UpdateGame(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;

	ClientData *localClient = jetClient.GetLocalClient();

	if (localClient)
	{
		// If we're connected, get the current input, save it to our
		// input history, and locally apply it to the local jet
		GameInput newInput = GetCurrentInput(gameTime);
		inputs.push_back(newInput);
		GameInputPacketReq gameInputPacket(newInput);
		jetClient.WritePacket(gameInputPacket, false);

		Jet &jet = localClient->jet;
		jet.Update(newInput, gameTime);

		camera.Update(dt, jet.GetForward(), jet.GetUp(), jet.GetRight());
		camera.SetPos(jet.GetPosition() + Vector3::Transform(Vector3(0, 0.25f, 1.1f), jet.GetRotation()) * 1.5f);
	}

	// Update interpolation for remote clients
	jetClient.Update(gameTime);

	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		gfk::Game::Exit();
	}

	if (Keyboard::IsKeyDown(Keys::Space))
	{
		vrCam.Recenter();
	}
}

GameInput JetGame::GetCurrentInput(const gfk::GameTime &gameTime)
{
	GameInput input;

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

	input.sequenceNumber = inputSequenceNumber++;
	input.mouseDiffX = diff.X;
	input.mouseDiffY = diff.Y;

	if (Keyboard::IsKeyDown(Keys::W))
	{
		input.keyW = true;
	}
	if (Keyboard::IsKeyDown(Keys::S))
	{
		input.keyS = true;
	}
	if (Keyboard::IsKeyDown(Keys::LeftShift))
	{
		input.keyLeftShift = true;
	}

	return input;
}

void JetGame::SendStateToServer(const gfk::GameTime &gameTime)
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

	for (const auto &player : jetClient.players)
	{
		Matrix world = Matrix::Identity;

		if (player.second.id == jetClient.localPlayerId)
		{
			world = player.second.jet.GetTransform() * Matrix::CreateRotationY(MathHelper::ToRadians(90.0f)) * Matrix::CreateScale(0.04f);
		}
		else
		{
			world = player.second.displayJet.GetTransform() * Matrix::CreateRotationY(MathHelper::ToRadians(90.0f)) * Matrix::CreateScale(0.04f);
		}

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
