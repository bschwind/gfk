#include "include/JetGame.hpp"
#include <GFK/Graphics/Color.hpp>
#include <GFK/Input/Keyboard.hpp>
#include <GFK/Input/Mouse.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>

namespace jetGame
{

JetGame::JetGame(const std::string &title, int width, int height) :
Game(title, width, height),
mesh("assets/Airplane F18 N120712.3DS")
{
	isFixedTimeStep = true;
	targetUpdateFramesPerSecond = 60;

	camera.screenWidth = width;
	camera.screenHeight = height;
}

JetGame::~JetGame()
{
	
}

void JetGame::Initialize()
{
	gfk::Game::Initialize();
	primBatch.Initialize();

	Device.SetClearColor(Color::Black);
}

void JetGame::LoadContent()
{

}

void JetGame::UnloadContent()
{

}

void JetGame::Update(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;
	camera.Update(dt);

	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		gfk::Game::Exit();
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

	Matrix world;

	int num = 10;

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			world = Matrix::CreateTranslation(Vector3((i-num*0.5) * 30, 0, (j-num*0.5) * 30)) * Matrix::CreateRotationX(gameTime.TotalGameTime + (interpolationFactor * gameTime.ElapsedGameTime));

			primBatch.Begin(PrimitiveType::TriangleList, camera, world);
			primBatch.DrawMesh(mesh);
			primBatch.End();
		}
	}

	Device.SwapBuffers();
}

}
