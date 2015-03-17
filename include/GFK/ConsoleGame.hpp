#pragma once

#include <GFK/System/GameTime.hpp>
#include <iostream>
#include <string>
#include <atomic>

namespace gfk
{

class ConsoleGame
{
public:
	ConsoleGame(bool isFixedTimeStep, int targetUpdateFramesPerSecond);
	virtual ~ConsoleGame();
	virtual void Initialize();
	virtual void UnloadContent();
	void Run();
	void Tick();
	void Exit();
protected:
	static std::atomic<bool> exitRequested;
	bool isFixedTimeStep;
	int targetUpdateFramesPerSecond;

	virtual void LoadContent();
	virtual void Update(const gfk::GameTime &gameTime);
private:
	gfk::GameTime time;
	double dt;
	double accumulator;
	double currentTime;

	static void SignalHandler(int signal);
};

}
