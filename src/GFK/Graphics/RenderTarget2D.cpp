#include <GFK/Graphics/RenderTarget2D.hpp>
#include <iostream>

namespace gfk
{

RenderTarget2D::RenderTarget2D(int width, int height) :
width(width),
height(height)
{
	// Generate the buffers
	glGenRenderbuffers(1, &depth);
	GLErrorCheck();
	glGenTextures(1, &color);
	GLErrorCheck();
	glGenFramebuffers(1, &frameBuffer);
	GLErrorCheck();

	// Set up the buffers
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindTexture(GL_TEXTURE_2D, color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::cout << "Made a render target!" << std::endl;
}

RenderTarget2D::~RenderTarget2D()
{
	if (frameBuffer)
	{
		glDeleteFramebuffers(1, &frameBuffer);
		frameBuffer = 0;
	}
	if (color)
	{
		glDeleteTextures(1, &color);
		color = 0;
	}
	if (depth)
	{
		glDeleteRenderbuffers(1, &depth);
		depth = 0;
	}
}

int RenderTarget2D::GetWidth() const
{
	return width;
}

int RenderTarget2D::GetHeight() const
{
	return height;
}

}
