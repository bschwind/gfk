#include <GFK/OSDetection.hpp>
#include <GFK/Game.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/MonitorConfig.hpp>
#include <GFK/Network/UDPSocket.hpp>
#if !defined(PLATFORM_ANDROID)
	#include <GFK/Input/Keyboard.hpp>
	#include <GFK/Input/Mouse.hpp>
	#include <signal.h>
#endif

namespace gfk
{

bool Game::exitRequested = false;

Game::Game() :
isFixedTimeStep(false),
title("GFK Game"),
width(1280),
height(720)
{

}

Game::Game(const std::string &gameTitle,
		   int screenWidth,
		   int screenHeight) :
isFixedTimeStep(false),
title(gameTitle),
width(screenWidth),
height(screenHeight)
{

}

Game::~Game()
{
	UDPSocket::ShutdownSocketLayer();
}

void Game::SignalHandler(int signal)
{
	if (signal == SIGINT)
	{
		// CTRL-C was pressed
		exitRequested = true;
	}
}

void Game::Initialize()
{
#if !defined(PLATFORM_ANDROID)
	// Catch signals such as CTRL-C
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = SignalHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);
#endif

	GameTime::InitClock();
	UDPSocket::InitializeSocketLayer();

	MonitorConfig::SetupMonitor(width, height, title, false);
	Device.SetClearColor(Color::CornflowerBlue);

#if !defined(PLATFORM_ANDROID)
	Keyboard::SetTargetWindow(Device.GetPrimaryWindow());
	Mouse::SetTargetWindow(Device.GetPrimaryWindow());
#endif

	time.TotalGameTime = GameTime::GetSystemTime();
	currentTime = GameTime::GetSystemTime();
	dt = 1.0 / targetUpdateFramesPerSecond;

	LoadContent();
#if !defined(PLATFORM_ANDROID)
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
			HandleEvents();

			Update(time);
			time.TotalGameTime += dt;
			accumulator -= dt;
		}

		double interpolationFactor = accumulator / dt;
		Draw(time, interpolationFactor);
	}
	else
	{
		double newTime = GameTime::GetSystemTime();
		time.ElapsedGameTime = newTime - time.TotalGameTime;
		time.TotalGameTime = newTime;

		HandleEvents();

		Update(time);
		Draw(time, 1.0f);
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
