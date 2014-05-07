#pragma once

#include <GFK/Game.hpp>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Mesh.hpp>

using namespace gfk;

namespace jetGame
{

class JetGame : public Game
{
public:
	JetGame(const std::string &title, int width, int height);
	~JetGame();

	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(const gfk::GameTime &gameTime);
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
	void ResizeWindow(int width, int height);
private:
	PrimitiveBatch3D primBatch;
	Camera camera;
	Mesh mesh;
};

}