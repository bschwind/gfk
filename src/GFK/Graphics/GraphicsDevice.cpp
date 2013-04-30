#include <GFK/Graphics/GraphicsDevice.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>

namespace gfk
{

GraphicsDevice::GraphicsDevice()
{

}

GraphicsDevice::~GraphicsDevice()
{

}

void GraphicsDevice::SetClearColor(const gfk::Color &color)
{
	glClearColor(color.R, color.G, color.B, color.A);
}

void GraphicsDevice::SetClearColor(const gfk::PackedColor &color)
{
	glClearColor(color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void GraphicsDevice::SetDepthClearValue(const float depth)
{
	glClearDepth(depth);
}

void GraphicsDevice::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::ClearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::ClearColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

}
