#include <GFK/Game.hpp>
#include <GFK/Graphics/Color.hpp>

namespace gfk
{

Game::Game() :
title("GFK Game"),
width(1280),
height(720)
{

}

Game::Game(const std::string &gameTitle,
		   const int screenWidth,
		   const int screenHeight) :
exitRequested(false),
title(gameTitle),
width(screenWidth),
height(screenHeight)
{

}

Game::~Game()
{
	
}

void Game::Initialize()
{
	Device.Initialize(title, width, height);
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
	Device.SwapBuffers();
}

void Game::Tick()
{
	//Get the elapsed and total game time
	// float dt = clock.getElapsedTime().asSeconds();
	// time.ElapsedGameTime = dt;
	// time.TotalGameTime += dt;
	// clock.restart();

	HandleEvents();
	Update(time);
	Draw(time);
}

void Game::Run()
{
	Initialize();
	while(!exitRequested && !Device.WindowShouldClose())
	{
		Tick();
	}

	// window.close();
	UnloadContent();
}

void Game::HandleEvents()
{
	Device.UpdateWindowEvents();
	//Check for close events
	// while (window.pollEvent(event))
	// {
	// 	// Window closed
	// 	if(event.type == sf::Event::Closed)
	// 	{
	// 		window.close();
	// 	}

	// 	if(event.type == sf::Event::Resized)
	// 	{
	// 		Device.ResizeWindow(event.size.width, event.size.height);
	// 	}	
	// }

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	// {
	// 	exitRequested = true;
	// }
}

void Game::Exit()
{
	exitRequested = true;
}

}
