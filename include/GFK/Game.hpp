#pragma once

#include <GFK/System/GameTime.hpp>
#include <GFK/Graphics/GraphicsDevice.hpp>
#include <iostream>
#include <string>
#include <atomic>

namespace gfk
{

class Game
{
public:
	Game();
	Game(const std::string &title, 
		 int screenWidth, 
		 int screenHeight);
	virtual ~Game();
	virtual void Initialize();
	virtual void UnloadContent();
	void Run();
	void Tick();
	virtual void ResizeWindow(int width, int height);
	void Exit();
protected:
	gfk::GraphicsDevice Device;
	static std::atomic<bool> exitRequested;
	bool isFixedTimeStep;
	int targetUpdateFramesPerSecond;

	virtual void LoadContent();
	virtual void Update(const gfk::GameTime &gameTime);
	virtual void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
private:
	gfk::GameTime time;
	std::string title;
	int width, height;
	void HandleEvents();
	double dt;
	double accumulator;
	double currentTime;

	static void SignalHandler(int signal);
	static void WindowResizeHandler(GLFWwindow *window, int width, int height);
};

}
