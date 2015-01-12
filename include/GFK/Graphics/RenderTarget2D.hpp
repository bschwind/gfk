#pragma once

#include <GFK/Graphics/GLHeader.hpp>

namespace gfk
{

class RenderTarget2D
{
public:
	RenderTarget2D(int width, int height);
	~RenderTarget2D();
	int GetWidth() const;
	int GetHeight() const;
	GLuint frameBuffer;
protected:
private:
	int width;
	int height;
	GLuint color;
	GLuint depth;
};

}
