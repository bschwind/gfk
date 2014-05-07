#include <GFK/OSDetection.hpp>
#include <GFK/Game.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/MonitorConfig.hpp>
#include <GFK/Network/UDPSocket.hpp>
#if not defined(PLATFORM_ANDROID)
	#include <GFK/Input/Keyboard.hpp>
	#include <GFK/Input/Mouse.hpp>
#endif

namespace gfk
{

Game::Game() :
exitRequested(false),
isFixedTimeStep(false),
title("GFK Game"),
width(1280),
height(720),
headless(false)
{

}

Game::Game(bool headless) :
exitRequested(false),
isFixedTimeStep(false),
title("GFK Game"),
headless(headless)
{

}

Game::Game(const std::string &gameTitle,
		   int screenWidth,
		   int screenHeight) :
exitRequested(false),
isFixedTimeStep(false),
title(gameTitle),
width(screenWidth),
height(screenHeight),
headless(false)
{

}

Game::~Game()
{
	UDPSocket::ShutdownSocketLayer();
}

void Game::Initialize()
{
	GameTime::InitClock();
	UDPSocket::InitializeSocketLayer();

	if (!headless)
	{
		MonitorConfig::SetupMonitor(width, height, title, false);
		Device.SetClearColor(Color::CornflowerBlue);

#if not defined(PLATFORM_ANDROID)
		Keyboard::SetTargetWindow(Device.GetPrimaryWindow());
		Mouse::SetTargetWindow(Device.GetPrimaryWindow());
#endif
	}

	time.TotalGameTime = GameTime::GetSystemTime();
	currentTime = GameTime::GetSystemTime();
	dt = 1.0 / targetFramesPerSecond;

	LoadContent();
#if not defined(PLATFORM_ANDROID)
	glfwSetTime(0.0);
#endif
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

void Game::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();
	Device.SwapBuffers();
}

void Game::Tick()
{
	if (isFixedTimeStep)
	{
		// Implementation from http://gafferongames.com/game-physics/fix-your-timestep/

		time.ElapsedGameTime = dt;

		double newTime = GameTime::GetSystemTime();
		double frameTime = newTime - currentTime;
		if (frameTime > 0.25)
		{
			// Avoid the "spiral of death"
			frameTime = 0.25;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			if (!headless)
			{
				HandleEvents();
			}

			Update(time);
			time.TotalGameTime += dt;
			accumulator -= dt;
		}

		if (!headless)
		{
			double interpolationFactor = accumulator / dt;
			Draw(time, interpolationFactor);
		}
	}
	else
	{
		double newTime = GameTime::GetSystemTime();
		time.ElapsedGameTime = newTime - time.TotalGameTime;
		time.TotalGameTime = newTime;

		if (!headless)
		{
			HandleEvents();
		}

		Update(time);

		if (!headless)
		{
			Draw(time, 1.0f);
		}
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

void Game::ResizeWindow(int width, int height)
{
	this->width = width;
	this->height = height;
	Device.ResizeWindow(width, height);
}

void Game::HandleEvents()
{
	Device.UpdateWindowEvents();
}

void Game::Exit()
{
	exitRequested = true;
}

}
