#pragma once

#include <string>
#include <vector>

struct GLFWwindow;

namespace gfk
{

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
	void Initialize();
	void ResizeWindow(int width, int height);
	void SwapBuffers();
	void UpdateWindowEvents();
	bool WindowShouldClose();
#if not defined(PLATFORM_ANDROID)
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
};
}
