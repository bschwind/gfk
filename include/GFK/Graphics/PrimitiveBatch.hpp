#pragma once

#include <GFK/Graphics/Shader.hpp>
#include <GFK/Math/Vector2.hpp>
#include <GFK/Graphics/PrimitiveType.hpp>

namespace gfk
{

class PrimitiveBatch
{
public:
	PrimitiveBatch();
	~PrimitiveBatch();

	void Initialize();
	void Begin(PrimitiveType primitiveType);
	void DrawLine(const Vector2 &v1, const Vector2 &v2);
	void DrawTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3);
	void DrawCircle(const Vector2 &center, float radius, int segments);
	void DrawPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments);
	void Draw2DGrid(int width, int height);
	void FillTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3);
	void FillQuad(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Vector2 &v4);
	void FillCircle(const Vector2 &center, float radius, int segments);
	void FillPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments);
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
	Shader shader;
	PrimitiveType primitiveType;

	void AddVertex(const Vector2 &vertex);
};

}