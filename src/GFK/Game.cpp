#include <GFK/Game.hpp>
#include <GFK/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

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
	window.close();
	UnloadContent();
}

void Game::Initialize()
{
	window.create(sf::VideoMode(width, height, 32), title);
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
	//std::cout << gameTime.ElapsedGameTime << std::endl;
}

void Game::Draw(const gfk::GameTime &gameTime)
{
	Device.Clear();
	window.display();
}

void Game::Tick()
{
	//Get the elapsed and total game time
	float dt = clock.getElapsedTime().asSeconds();
	time.ElapsedGameTime = dt;
	time.TotalGameTime += dt;
	clock.restart();

	HandleEvents();
	Update(time);
	Draw(time);
}

void Game::Run()
{
	Initialize();
	while(!exitRequested && window.isOpen())
	{
		Tick();
	}
}

void Game::HandleEvents()
{
	//Check for close events
	while (window.pollEvent(event))
	{
		// Window closed
		if(event.type == sf::Event::Closed)
		{
			window.close();
		}

		if(event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
		}	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}
}

void Game::Exit()
{
	exitRequested = true;
}

}