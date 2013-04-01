#include <GFK/Game.hpp>
#include <GFK/Vector2.hpp>
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

Game::Game(const std::string &gameTitle,
		   const int screenWidth,
		   const int screenHeight) :
clock(),
time(),
title(gameTitle),
width(screenWidth),
height(screenHeight)
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
	window.Create(sf::VideoMode(width, height, 32), title);
	Device = GraphicsDevice();
	Device.SetClearColor(Color::CornflowerBlue);
	LoadContent();
}

void Game::LoadContent()
{

}

void Game::UnloadContent()
{

}

void Game::Update(const gfk::GameTime &gameTime)
{
	std::cout << gameTime.ElapsedGameTime << std::endl;
}

void Game::Draw(const gfk::GameTime &gameTime)
{
	Device.Clear();
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
		if(event.Type == sf::Event::Closed)
		{
			window.Close();
		}

		// Escape key pressed
		if((event.Type == sf::Event::KeyPressed)
			&& (event.Key.Code == sf::Key::Escape))
		{
			window.Close();
		}
		if(event.Type == sf::Event::Resized)
		{
			glViewport(0, 0, event.Size.Width, event.Size.Height);
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