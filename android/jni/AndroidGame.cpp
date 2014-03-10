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
	Device.SetClearColor(Color::CornflowerBlue);
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
}

void AndroidGame::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();
}
