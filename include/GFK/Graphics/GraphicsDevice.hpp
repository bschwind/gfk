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

	void SetClearColor(const gfk::Color &color);
	void SetClearColor(const gfk::PackedColor &color);
	void SetDepthClearValue(float depth);
	void Clear();
	void ClearDepth();
	void ClearColor();
	void Display();
	void Initialize(const gfk::Game &game);
	void ResizeWindow(int width, int height);
	void SwapBuffers();
	void UpdateWindowEvents();
	bool WindowShouldClose();
#if !defined(PLATFORM_ANDROID)
	GLFWwindow* GetPrimaryWindow();
	std::vector<GLFWwindow*> GetWindows();
#endif
protected:

private:
	GLFWwindow* primaryWindow;
	std::vector<GLFWwindow*> windows;
	bool gameShouldClose;
	static void error_callback(int error, const char* description);
	void InitializeGLEW();
	void InitializeWindows();
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
