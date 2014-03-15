#pragma once

#include <GFK/Game.hpp>
#include <GFK/Graphics/Camera2D.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Math/Vector2.hpp>

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
	void ResizeWindow(int width, int height);
private:
	PrimitiveBatch3D primBatch;
	Camera camera;
};
