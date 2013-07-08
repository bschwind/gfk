#pragma once

#include <string>

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
	void Initialize(const std::string &title, int width, int height);
	void ResizeWindow(int width, int height);
	void SwapBuffers();
	void UpdateWindowEvents();
	bool WindowShouldClose();
protected:

private:
	GLFWwindow* window;
	static void error_callback(int error, const char* description);
};
}
