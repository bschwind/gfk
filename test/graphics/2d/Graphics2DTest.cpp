#include <string>
#include <iostream>
#include <GFK/Game.hpp>
#include <GFK/Graphics/Camera2D.hpp>
#include <GFK/Graphics/PrimitiveBatch2D.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Input/Keyboard.hpp>
#include <GFK/Input/Mouse.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Math/Vector2.hpp>

using namespace gfk;

class Graphics2DTest : public Game
{
public:
	Graphics2DTest(const std::string &title, int width, int height);
	~Graphics2DTest();

	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(const gfk::GameTime &gameTime);
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
private:
	PrimitiveBatch2D primBatch;
	Camera2D camera;
};

Graphics2DTest::Graphics2DTest(const std::string &title, int width, int height) :
Game(title, width, height)
{

}

Graphics2DTest::~Graphics2DTest()
{
	
}

void Graphics2DTest::Initialize()
{
	gfk::Game::Initialize();
	primBatch.Initialize();

	camera.screenWidth = 1280;
	camera.screenHeight = 720;

	Device.SetClearColor(Color::White);
}

void Graphics2DTest::LoadContent()
{

}

void Graphics2DTest::UnloadContent()
{

}

void Graphics2DTest::Update(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;
	camera.Update(dt);

	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		gfk::Game::Exit();
	}
}

void drawLine(const Vector2 &p1, const Vector2 &p2, float thickness, const Color &color, PrimitiveBatch2D &primBatch)
{
	float alpha = 1.0f;
	Color drawColor = color;

	if (thickness < 1.0f) {
		alpha = thickness;
		thickness = 1.0f;
	}

	drawColor.A = alpha;

	// Possibly approximate normal if the line is thin
	Vector2 normal = Vector2::PerProduct(p2 - p1);
	normal.Normalize();

	primBatch.FillQuad(
		p1 + (normal * thickness * 0.5f),
		p2 + (normal * thickness * 0.5f),
		p2 - (normal * thickness * 0.5f),
		p1 - (normal * thickness * 0.5f),
		drawColor);
}

void Graphics2DTest::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	primBatch.Begin(PrimitiveType::TriangleList, camera);

	for (int i = 0; i < 100; i++) {
		float thickness = 0.03f + (i * 0.3f);

		drawLine(
			Vector2(i * 11 + thickness, 0),
			Vector2(100 + thickness + (i * 11), 400),
			thickness,
			Color::Black,
			primBatch);
	}

	primBatch.End();

	Device.SwapBuffers();
}

int main()
{
	Graphics2DTest game("Graphics 2D Test", 1280, 720);
	game.Run();
	return 0;
}
