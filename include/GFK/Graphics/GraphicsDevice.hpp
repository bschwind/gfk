#pragma once

#include <string>
#include <vector>
#include <GFK/Graphics/GLHeader.hpp>
#include <GFK/OSDetection.hpp>

struct GLFWwindow;

namespace gfk
{

class Game;
class Color;
class PackedColor;

class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	enum GraphicsState
	{
		Uninitialized,
		Initialized
	};

	GraphicsState state;

	void SetClearColor(const gfk::Color &color);
	void SetClearColor(const gfk::PackedColor &color);
	void SetDepthClearValue(float depth);
	void Clear();
	void ClearDepth();
	void ClearColor();
	void Display();
	void Initialize(const gfk::Game &game);
	void Uninitialize();
	void ResizeWindow(int width, int height);
	void SwapBuffers();
	void UpdateWindowEvents();
	bool WindowShouldClose();
#if !defined(PLATFORM_MOBILE)
	GLFWwindow* GetPrimaryWindow();
#endif
protected:

private:
	GLFWwindow* primaryWindow;
	bool gameShouldClose;
	static void error_callback(int error, const char* description);
	void InitializeGLEW();
	void InitializeWindow(const gfk::Game &game);
#if defined(PLATFORM_ANDROID)

	struct AndroidSurface {
		EGLDisplay display;
		EGLSurface surface;
		EGLContext context;
	};


	AndroidSurface androidSurface;

	int InitializeAndroid(const gfk::Game &game);
	void UninitializeAndroid();
#endif
};
}
