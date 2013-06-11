#include <GFK/Graphics/GraphicsDevice.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/PackedColor.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <string>

namespace gfk
{

GLfloat vertices_position[24] = {
		0.0, 0.0,
		0.5, 0.0,
		0.5, 0.5,
		
		0.0, 0.0,
		0.0, 0.5,
		-0.5, 0.5,
		
		0.0, 0.0,
		-0.5, 0.0,
		-0.5, -0.5,		

		0.0, 0.0,
		0.0, -0.5,
		0.5, -0.5,
	};

GraphicsDevice::GraphicsDevice()
{

}

GraphicsDevice::~GraphicsDevice()
{

}

void GraphicsDevice::Initialize()
{
	//glewInit();
	// Create a Vertex Buffer Object that will store the vertices on video memory
	// GLuint vbo;
	// glGenBuffers(1, &vbo);

	// // Allocate space and upload the data from CPU to GPU
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// std::cout << sizeof(vertices_position) << std::endl;
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);
}

void GraphicsDevice::SetClearColor(const gfk::Color &color)
{
	glClearColor(color.R, color.G, color.B, color.A);
}

void GraphicsDevice::SetClearColor(const gfk::PackedColor &color)
{
	glClearColor(color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void GraphicsDevice::SetDepthClearValue(float depth)
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

void GraphicsDevice::ResizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

}
