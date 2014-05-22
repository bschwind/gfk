#pragma once

#include <GFK/GameTime.hpp>
#include <GFK/Graphics/GraphicsDevice.hpp>
#include <iostream>
#include <string>

namespace gfk
{

class Game
{
public:
	Game();
	Game(bool headless);
	Game(const std::string &title, 
		 int screenWidth, 
		 int screenHeight);
	~Game();
	virtual void Initialize();
	virtual void UnloadContent();
	void Run();
	void Tick();
	void ResizeWindow(int width, int height);
	void Exit();
protected:
	gfk::GraphicsDevice Device;
	static bool exitRequested;
	bool isFixedTimeStep;
	int targetFramesPerSecond = 60;

	virtual void LoadContent();
	virtual void Update(const gfk::GameTime &gameTime);
	virtual void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
private:
	gfk::GameTime time;
	std::string title;
	int width, height;
	void HandleEvents();
	bool headless;
	double dt;
	double accumulator = 0.0;
	double currentTime = 0.0;

	static void SignalHandler(int signal);
};

}
