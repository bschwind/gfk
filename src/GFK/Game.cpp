#include <GFK/Game.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/MonitorConfig.hpp>
#include <GLFW/glfw3.h>

namespace gfk
{

Game::Game() :
exitRequested(false),
title("GFK Game"),
width(1280),
height(720),
headless(false)
{

}

Game::Game(bool headless) :
exitRequested(false),
title("GFK Game"),
headless(headless)
{

}

Game::Game(const std::string &gameTitle,
		   const int screenWidth,
		   const int screenHeight) :
exitRequested(false),
title(gameTitle),
width(screenWidth),
height(screenHeight),
headless(false)
{

}

Game::~Game()
{
	
}

void Game::Initialize()
{
	GameTime::InitClock();

	if (!headless)
	{
		MonitorConfig::SetupMonitor(width, height, title, false);
		Device.Initialize();
		Device.SetClearColor(Color::CornflowerBlue);
	}

	time.TotalGameTime = GameTime::GetSystemTime();

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
	std::cout << (gameTime.TotalGameTime) << std::endl;
}

void Game::Draw(const gfk::GameTime &gameTime)
{
	Device.Clear();
	Device.SwapBuffers();
}

void Game::Tick()
{
	//Get the elapsed and total game time
	double currentTime = GameTime::GetSystemTime();
	time.ElapsedGameTime = currentTime - time.TotalGameTime;
	time.TotalGameTime = currentTime;

	if (!headless)
	{
		HandleEvents();
	}

	Update(time);

	if (!headless)
	{
		Draw(time);
	}
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
