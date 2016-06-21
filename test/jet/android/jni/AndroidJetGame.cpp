#include "AndroidJetGame.hpp"
#include "network/Packet.hpp"
#include "objects/Jet.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/Input/TouchEvent.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/System/Logger.hpp>
#include <GFK/Network/NetDiscoveryClient.hpp>
#include <sstream>
#include <cmath>

using namespace gfk;

namespace jetGame
{

AndroidJetGame::AndroidJetGame(android_app *app) :
Game(app),
networkCounter(0),
networkSendsPerSecond(10),
mesh()
{
	Logger::Log("Jet Game Constructor!");
	isFixedTimeStep = true;
	targetUpdateFramesPerSecond = 60;
}

AndroidJetGame::~AndroidJetGame()
{
	Logger::Log("Jet Game Destructor!");
	jetClient.DisconnectFromServer();
}

void AndroidJetGame::Initialize()
{
	Logger::Log("initialize()!");
	gfk::Game::Initialize();

	std::unordered_set<IPAddress> hosts = NetDiscoveryClient::FindHosts(55778, 1.0);

	if (hosts.size() > 0)
	{
		const IPAddress &firstHost = *hosts.cbegin();

		Logger::Log(firstHost.GetIPV4String());
		jetClient.ConnectToServer(firstHost.GetIPV4String(), firstHost.GetPort(), ClientType::GFK_ANDROID);
	}
	else
	{
		jetClient.ConnectToServer("192.168.24.53", 55777, ClientType::GFK_ANDROID);
	}
}

void AndroidJetGame::LoadContent()
{
	gfk::Game::LoadContent();
	Logger::Logf("load content()!");

	primBatch.Initialize();
	mesh.Load("f18Hornet.3DS", GetAndroidApp());
	Device.SetClearColor(Color::Black);
}

void AndroidJetGame::UnloadContent()
{
	gfk::Game::UnloadContent();
	Logger::Log("unload content()!");
}

TouchEvent currentTouchEvent;

void AndroidJetGame::OnTouchEvent(const TouchEvent &event)
{
	recognizer.OnTouchEvent(event);
	currentTouchEvent = event;
}

void AndroidJetGame::Update(const gfk::GameTime &gameTime)
{
	recognizer.Update(gameTime);
	UpdateNetwork(gameTime);
	UpdateGame(gameTime);
	SendStateToServer(gameTime);
}

void AndroidJetGame::UpdateNetwork(const gfk::GameTime &gameTime)
{
	jetClient.ProcessIncomingPackets(gameTime);
}

void AndroidJetGame::UpdateGame(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;
	double totalTime = gameTime.TotalGameTime;
	jetClient.Update(gameTime);
}

void AndroidJetGame::SendStateToServer(const gfk::GameTime &gameTime)
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

float rotation = 0.0f;

void AndroidJetGame::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	Color color = Color::Gray;
	color.A = 0.3f;

	Vector2 panOffset = recognizer.GetPanOffset();
	// Logger::Logf("Pan Accum: (%f,%f)\n", panOffset.X, panOffset.Y);

	float rotateOffset = recognizer.GetRotationOffset();
	rotation += rotateOffset;
	cam.SetYRot(rotation);

	primBatch.Begin(PrimitiveType::LineList, cam);
	primBatch.DrawXZGrid(-200, -200, 200, 200, color);
	primBatch.End();

	for (const auto &player : jetClient.players)
	{
		Matrix world = player.second.displayJet.GetTransform() * Matrix::CreateRotationY(MathHelper::ToRadians(90.0f)) * Matrix::CreateScale(0.04f);
		float jetX = player.second.displayJet.GetPosition().X;
		float jetY = player.second.displayJet.GetPosition().Y;
		float jetZ = player.second.displayJet.GetPosition().Z;

		primBatch.Begin(PrimitiveType::TriangleList, cam, world);
		primBatch.DrawMesh(mesh);
		primBatch.End();

		primBatch.Begin(PrimitiveType::LineList, cam);
		primBatch.DrawLine(Vector3(jetX, 0, jetZ), Vector3(jetX, jetY, jetZ), Color::Red, Color::Red);
		primBatch.DrawLine(Vector3(), Vector3(jetX, jetY, jetZ), Color::Green, Color::Green);
		primBatch.End();
	}

	primBatch.Begin(PrimitiveType::TriangleList, cam, Matrix::CreateRotationY(MathHelper::ToRadians(90.0f)) * Matrix::CreateScale(0.04f));
	primBatch.DrawMesh(mesh);
	primBatch.End();

	Matrix projection = Matrix::CreateOrthographicUpperLeftOrigin(GetWidth(), GetHeight(), 0.0f, 100.0f);
	Matrix view = Matrix::CreateLookAt(Vector3(0, 0, 1.0f), Vector3(0, 0, -1.0f), Vector3::Up);

	for (int i = 0; i < currentTouchEvent.numTouches; i++)
	{
		Matrix world = Matrix::CreateTranslation(Vector3(currentTouchEvent.touchPoints[i].pos.X, currentTouchEvent.touchPoints[i].pos.Y, 0)) * Matrix::Identity * Matrix::CreateRotationY(MathHelper::ToRadians(90.0f)) * Matrix::CreateScale(20.0f);
		// primBatch.DrawSphere(Vector3(currentTouchEvent.touchPoints[i].pos.X, currentTouchEvent.touchPoints[i].pos.Y, 0), 100.0f, 10, 10, Color::Red);
		primBatch.Begin(PrimitiveType::TriangleList, view, projection, world);
		primBatch.DrawMesh(mesh);
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
