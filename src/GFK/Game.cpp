#include <GFK/Game.hpp>
#include <iostream>
#include <string>

namespace gfk
{

Game::Game() :
clock(),
time()
{

}

Game::Game(const std::string& gameTitle) :
clock(),
time(),
title(gameTitle)
{

}

Game::~Game()
{

}

void Game::Initialize()
{

}

void Game::LoadContent()
{

}

void Game::UnloadContent()
{

}

void Game::Update(const gfk::GameTime gameTime)
{
	std::cout << gameTime.TotalGameTime << std::endl;
}

void Game::Draw(const gfk::GameTime gameTime)
{

}

void Game::Tick()
{
	double dt = clock.GetElapsedTime();
	time.ElapsedGameTime = dt;
	time.TotalGameTime += dt;
	clock.Reset();

	Update(time);
	Draw(time);
}

void Game::Run()
{
	while(!exitRequested)
	{
		Tick();
	}
}

}
