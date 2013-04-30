#pragma once

#include <GFK/GameTime.hpp>
#include <GFK/Graphics/GraphicsDevice.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

namespace gfk
{

class Game
{
public:
	Game();
	Game(const std::string &title, 
		 const int screenWidth, 
		 const int screenHeight);
	~Game();
	void Run();
	void Exit();
protected:
	gfk::GraphicsDevice Device;
	bool exitRequested;

	virtual void Initialize();
	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(const gfk::GameTime &gameTime);
	virtual void Draw(const gfk::GameTime &gameTime);
private:
	sf::Clock clock;
	sf::Window window;
	sf::Event event;
	gfk::GameTime time;
	std::string title;
	int width, height;
	void HandleEvents();
	void Tick();
};

}
