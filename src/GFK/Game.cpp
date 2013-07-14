#include <GFK/Game.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/MonitorConfig.hpp>
#include <GLFW/glfw3.h>

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
	MonitorConfig::SetupMonitor(1280, 720, title, false);
	MonitorConfig::SetupMonitor(1280, 720, title, false);

	Device.Initialize();
	Device.SetClearColor(Color::CornflowerBlue);

	time.TotalGameTime = glfwGetTime();

	LoadContent();
	glfwSetTime(0.0);
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
	double currentTime = glfwGetTime();
	time.ElapsedGameTime = currentTime - time.TotalGameTime;
	time.TotalGameTime = currentTime;

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
