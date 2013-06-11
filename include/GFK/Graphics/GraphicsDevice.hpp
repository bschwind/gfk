#pragma once

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
	void Initialize();
	void ResizeWindow(int width, int height);
protected:

private:

};
}
