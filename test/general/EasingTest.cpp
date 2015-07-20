#include <string>
#include <iostream>
#include <GFK/Game.hpp>
#include <GFK/Graphics/Camera2D.hpp>
#include <GFK/Graphics/PrimitiveBatch2D.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Input/Keyboard.hpp>
#include <GFK/Input/Mouse.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Math/EasingFunctions.hpp>
#include <GFK/Math/Vector2.hpp>

using namespace gfk;

class EasingTest : public Game
{
public:
	EasingTest(const std::string &title, int width, int height);
	~EasingTest();

	void Initialize();
	void LoadContent();
	void UnloadContent();
	void Update(const gfk::GameTime &gameTime);
	void Draw(const gfk::GameTime &gameTime, float interpolationFactor);
private:
	PrimitiveBatch2D primBatch;
	Camera2D camera;
	float t, duration;
};

EasingTest::EasingTest(const std::string &title, int width, int height) :
Game(title, width, height),
t(0.0f),
duration(2.5f)
{
	camera.SetScreenWidth(width);
	camera.SetScreenHeight(height);
}

EasingTest::~EasingTest()
{
	
}

void EasingTest::Initialize()
{
	gfk::Game::Initialize();
}

void EasingTest::LoadContent()
{
	primBatch.Initialize();
	Device.SetClearColor(Color::White);
}

void EasingTest::UnloadContent()
{

}

void EasingTest::Update(const gfk::GameTime &gameTime)
{
	float dt = gameTime.ElapsedGameTime;

	if (Keyboard::IsKeyDown(Keys::Escape))
	{
		gfk::Game::Exit();
	}

	t += dt;

	if (t > duration)
	{
		t = 0.0f;
	}
}

void DrawEasingTriangle(float x, float y, float startY, float endY, PrimitiveBatch2D &primBatch)
{
	primBatch.FillQuad(Vector2(x - 0.5f, endY), Vector2(x + 0.5f, endY), Vector2(x + 0.5f, startY), Vector2(x - 0.5f, startY), Color::Black);
	primBatch.FillTriangle(Vector2(x, y), Vector2(x + 10, y - 10), Vector2(x + 10, y + 10), Color::Red, Color::Red, Color::Red);
}

void EasingTest::Draw(const gfk::GameTime &gameTime, float interpolationFactor)
{
	Device.Clear();

	primBatch.Begin(PrimitiveType::TriangleList, camera);

	float x = 1;

	float startY = 600;
	float endY = 300;
	float gap = 28;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInBack(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutBack(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutBack(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInBounce(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutBounce(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutBounce(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInCirc(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutCirc(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutCirc(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInCubic(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutCubic(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutCubic(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInElastic(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutElastic(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutElastic(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInExpo(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutExpo(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutExpo(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInLinear(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutLinear(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutLinear(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInQuad(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutQuad(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutQuad(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInQuart(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutQuart(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutQuart(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInQuint(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutQuint(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutQuint(t, startY, endY-startY, duration), startY, endY, primBatch);

	x += gap;

	DrawEasingTriangle(x += gap, EasingFunctions::EaseInSine(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseOutSine(t, startY, endY-startY, duration), startY, endY, primBatch);
	DrawEasingTriangle(x += gap, EasingFunctions::EaseInOutSine(t, startY, endY-startY, duration), startY, endY, primBatch);

	primBatch.End();

	Device.SwapBuffers();
}

int main()
{
	EasingTest game("Easing Test", 1280, 720);
	game.Run();
	return 0;
}
