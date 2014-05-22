#pragma once

#include <GFK/GameTime.hpp>
#include <iostream>
#include <string>

namespace gfk
{

class ConsoleGame
{
public:
	ConsoleGame();
	~ConsoleGame();
	virtual void Initialize();
	virtual void UnloadContent();
	void Run();
	void Tick();
	void Exit();
protected:
	static bool exitRequested;
	bool isFixedTimeStep;
	int targetUpdateFramesPerSecond = 60;

	virtual void LoadContent();
	virtual void Update(const gfk::GameTime &gameTime);
private:
	gfk::GameTime time;
	double dt;
	double accumulator = 0.0;
	double currentTime = 0.0;

	static void SignalHandler(int signal);
};

}
