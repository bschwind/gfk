#include "AndroidGame.hpp"
#include <GFK/Graphics/Color.hpp>

using namespace gfk;

AndroidGame::AndroidGame() :
Game()
{

}

AndroidGame::~AndroidGame()
{
	
}

void AndroidGame::Initialize()
{
	gfk::Game::Initialize();
	primBatch.Initialize();
	camera.pos = Vector3(10, 5, 12);

	Device.SetClearColor(Color::Black);
}

void AndroidGame::LoadContent()
{

}

void AndroidGame::UnloadContent()
{

}

void AndroidGame::Update(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;
	camera.Update(dt);
}

void AndroidGame::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	// Draw world grid and axis references
	primBatch.Begin(PrimitiveType::LineList, camera);
	Color color = Color::Gray;
	color.A = 0.3f;
	primBatch.DrawXZGrid(-200, -200, 200, 200, color);
	primBatch.DrawXYGrid(-200, 0, 200, 200, color);
	primBatch.DrawYZGrid(0, -200, 200, 200, color);
	primBatch.DrawLine(Vector3::Zero, Vector3::UnitX, Color::Red, Color::Red);
	primBatch.DrawLine(Vector3::Zero, Vector3::UnitY, Color::Green, Color::Green);
	primBatch.DrawLine(Vector3::Zero, Vector3::UnitZ, Color::Blue, Color::Blue);
	primBatch.End();

	// Draw simple jet
	Matrix world = Matrix::CreateRotationZ(gameTime.TotalGameTime);
	primBatch.Begin(PrimitiveType::TriangleList, camera, world);
	primBatch.FillBox(Vector3(0, 0, 0), Vector3(3, 0.07f, 0.5f), Color::White);
	primBatch.FillBox(Vector3(0, -0.3f, 2), Vector3(0.3f, 0.3f, 3), Color::White);
	primBatch.End();

	Device.SwapBuffers();
}

void AndroidGame::ResizeWindow(int width, int height)
{
	gfk::Game::ResizeWindow(width, height);
	camera.screenWidth = width;
	camera.screenHeight = height;
}
