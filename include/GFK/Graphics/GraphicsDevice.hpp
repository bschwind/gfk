#pragma once

#include <SFML/Window.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/PackedColor.hpp>

namespace gfk
{
class GraphicsDevice
{
public:
	GraphicsDevice();
	~GraphicsDevice();

	void SetClearColor(const gfk::Color &color);
	void SetClearColor(const gfk::PackedColor &color);
	void SetDepthClearValue(const float depth);
	void Clear();
	void ClearDepth();
	void ClearColor();
protected:

private:

};
}
