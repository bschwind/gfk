#include <GFK/OSDetection.hpp>
#include <GFK/ConsoleGame.hpp>
#include <GFK/Network/UDPSocket.hpp>
#include <signal.h>

namespace gfk
{

std::atomic<bool> ConsoleGame::exitRequested(false);

ConsoleGame::ConsoleGame(bool isFixedTimeStep, int targetUpdateFramesPerSecond) :
isFixedTimeStep(isFixedTimeStep),
targetUpdateFramesPerSecond(targetUpdateFramesPerSecond),
accumulator(0.0),
currentTime(0.0)
{

}

ConsoleGame::~ConsoleGame()
{
	UDPSocket::ShutdownSocketLayer();
}

void ConsoleGame::SignalHandler(int signal)
{
	if (signal == SIGINT)
	{
		// CTRL-C was pressed
		exitRequested = true;
	}
}

void ConsoleGame::Initialize()
{
#if !defined(PLATFORM_WINDOWS)
	// Catch signals such as CTRL-C
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = SignalHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;

	sigaction(SIGINT, &sigIntHandler, NULL);
#endif

	GameTime::InitClock();
	UDPSocket::InitializeSocketLayer();

	time.TotalGameTime = GameTime::GetSystemTime();
	currentTime = GameTime::GetSystemTime();
	dt = 1.0 / targetUpdateFramesPerSecond;

	LoadContent();
}

void ConsoleGame::LoadContent()
{

}

void ConsoleGame::UnloadContent()
{

}

void ConsoleGame::Update(const gfk::GameTime &gameTime)
{

}

void ConsoleGame::Tick()
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
			Update(time);
			time.TotalGameTime += dt;
			accumulator -= dt;
		}
	}
	else
	{
		double newTime = GameTime::GetSystemTime();
		time.ElapsedGameTime = newTime - time.TotalGameTime;
		time.TotalGameTime = newTime;

		Update(time);
	}
}

void ConsoleGame::Run()
{
	Initialize();

	while(!exitRequested)
	{
		Tick();
	}

	UnloadContent();
}

void ConsoleGame::Exit()
{
	exitRequested = true;
}

}
