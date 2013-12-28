#pragma once

#include <string>
#include <vector>
#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Graphics/Camera.hpp>

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
protected:

private:
	GLFWwindow* primaryWindow;
	std::vector<GLFWwindow*> windows;
	bool gameShouldClose;
	static void error_callback(int error, const char* description);
	void InitializeWindows();
	PrimitiveBatch3D primBatch;
	Camera camera;
};
}
