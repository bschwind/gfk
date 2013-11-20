#pragma once

#include <GFK/Graphics/Shader.hpp>
#include <GFK/Math/Vector2.hpp>

namespace gfk
{

class PrimitiveBatch
{
public:
	PrimitiveBatch();
	~PrimitiveBatch();

	void Initialize();
	void Begin();
	void DrawLine(const Vector2 &v1, const Vector2 &v2);
	void End();
	void Flush();
protected:
private:
	GLuint vao;
	GLuint vbo;
	bool hasBegun;
	static const int bufferSize = 1024;
	unsigned int vertCounter;
	GLfloat vertexBuffer[bufferSize];

	void AddVertex(const Vector2 &vertex);
};

}