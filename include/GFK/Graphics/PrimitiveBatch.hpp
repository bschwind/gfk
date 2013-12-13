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
	void End();
	void Flush();

	void AddVertex(const Vector2 &vertex, const Color &color);

	void DrawLine(const Vector2 &v1, const Vector2 &v2, const Color &color1, const Color &color2);
	void DrawTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Color &color1, const Color &color2, const Color &color3);
	void DrawCircle(const Vector2 &center, float radius, int segments, const Color &color);
	void DrawPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments, const Color &color);
	void Draw2DGrid(int width, int height, const Color &color);

	void FillTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Color &color1, const Color &color2, const Color &color3);
	void FillQuad(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Vector2 &v4, const Color &color);
	void FillCircle(const Vector2 &center, float radius, int segments, const Color &color);
	void FillPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments, const Color &color);
protected:
private:
	struct VertexPositionColor {
		Vector2 Position;
		Color Color;
	};

	static const int bufferSize = 1024;
	VertexPositionColor vertexBuffer[bufferSize];
	GLuint vao;
	GLuint vbo;
	Shader shader;
	PrimitiveType primitiveType;
	bool hasBegun;
	unsigned int vertCounter;
};

}
