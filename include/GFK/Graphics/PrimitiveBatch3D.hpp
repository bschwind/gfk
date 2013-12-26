#pragma once

#include <GFK/Graphics/Shader.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Graphics/PrimitiveType.hpp>

namespace gfk
{

class PrimitiveBatch3D
{
public:
	PrimitiveBatch3D();
	~PrimitiveBatch3D();

	void Initialize();
	void Begin(PrimitiveType primitiveType);
	void End();
	void Flush();

	void AddVertex(const Vector3 &vertex, const Color &color);

	void DrawLine(const Vector3 &v1, const Vector3 &v2, const Color &color1, const Color &color2);
	void DrawTriangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color1, const Color &color2, const Color &color3);
	void DrawXYGrid(int width, int height, const Color &color);
	void DrawXZGrid(int width, int height, const Color &color);
	void DrawYZGrid(int width, int height, const Color &color);

	void FillTriangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color1, const Color &color2, const Color &color3);
	void FillQuad(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector3 &v4, const Color &color);
	void FillSphere(const Vector3 &pos, float radius, int verticalSegments, int radialSegments, const Color &color);
protected:
private:
	struct VertexPositionColor {
		Vector3 Position;
		Color Color;
	};

	// bufferSize must be a multiple of 3
	static const int bufferSize = 512 * 3;
	VertexPositionColor vertexBuffer[bufferSize];
	GLuint vao;
	GLuint vbo;
	Shader shader;
	PrimitiveType primitiveType;
	bool hasBegun;
	unsigned int vertCounter;
};

}