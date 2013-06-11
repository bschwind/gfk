#include <GL/glew.h>
#include <GFK/Game.hpp>
#include <GFK/Math/Vector2.hpp>
#include <GFK/Graphics/Color.hpp>
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
}

void Game::Initialize()
{
	window.create(sf::VideoMode(width, height, 32), title);
	// GLenum err = glewInit();
	// std::cout << GLEW_OK << std::endl;
	// if (GLEW_OK != err)
	// {
	// 	std::cout << "Fuck" << std::endl;
	// 	// Problem: glewInit failed, something is seriously wrong. 
	// 	fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	// }

	// // std::cout << &glGenBuffers << std::endl;
	// // GLuint vbo;
	// // glGenBuffers(1, &vbo);
	// // glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// // std::cout << sizeof(vertices_position) << std::endl;
	// // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);

	Device = GraphicsDevice();
	Device.Initialize();
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

	window.close();
	UnloadContent();
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
			Device.ResizeWindow(event.size.width, event.size.height);
		}	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		exitRequested = true;
	}
}

void Game::Exit()
{
	exitRequested = true;
}

}
