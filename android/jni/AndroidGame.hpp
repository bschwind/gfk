#pragma once

#include <GFK/Game.hpp>

using namespace gfk;

class AndroidGame : public Game
{
public:
	AndroidGame();
	~AndroidGame();

	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(const gfk::GameTime &gameTime);
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
};
