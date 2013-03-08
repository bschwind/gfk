#include <GFK/Game.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

namespace gfk
{

Game::Game() :
clock(),
time(),
title("GFK Game")
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
	std::cout << "Calling Game's destructor" << std::endl;
	window.Close();
	UnloadContent();
}

void Game::Initialize()
{
	//Initialize graphics device
	Device = GraphicsDevice();
	window.Create(sf::VideoMode(800, 600, 32), title);
	LoadContent();
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
	window.Display();
}

void Game::Tick()
{
	//Get the elapsed and total game time
	double dt = clock.GetElapsedTime();
	time.ElapsedGameTime = dt;
	time.TotalGameTime += dt;
	clock.Reset();

	//Check for close events
	while (window.GetEvent(event))
	{
		// Window closed
		if (event.Type == sf::Event::Closed)
		{
			window.Close();
		}

		// Escape key pressed
		if ((event.Type == sf::Event::KeyPressed) && (event.Key.Code == sf::Key::Escape))
		{
			window.Close();
		}
	}

	Update(time);
	Draw(time);
}

void Game::Run()
{
	Initialize();
	while(!exitRequested && window.IsOpened())
	{
		Tick();
	}
}

void Game::Exit()
{
	exitRequested = true;
}

}
