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
	void Run();
	void Exit();
protected:
	gfk::GraphicsDevice Device;
	bool exitRequested;
	bool isFixedTimeStep;
	int targetFramesPerSecond = 60;

	virtual void Initialize();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(const gfk::GameTime &gameTime);
	virtual void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
private:
	gfk::GameTime time;
	std::string title;
	int width, height;
	void HandleEvents();
	void Tick();
	bool headless;
	double dt;
	double accumulator = 0.0;
	double currentTime = 0.0;
};

}
