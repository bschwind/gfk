#pragma once

#include <GFK/Graphics/Shader.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Graphics/PrimitiveType.hpp>
#include <GFK/Graphics/Camera.hpp>

namespace gfk
{

class PrimitiveBatch3D
{
public:
	PrimitiveBatch3D();
	~PrimitiveBatch3D();

	void Initialize();
	void Begin(PrimitiveType primitiveType, Camera &camera);
	void Begin(PrimitiveType primitiveType, Camera &camera, const Matrix &worldMatrix);
	void Flush();
	void End();

	void AddVertex(const Vector3 &vertex, const Color &color);

	void DrawLine(const Vector3 &v1, const Vector3 &v2, const Color &color1, const Color &color2);
	void DrawTriangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color1, const Color &color2, const Color &color3);
	void DrawQuad(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector3 &v4, const Color &color);
	void DrawXYGrid(int width, int height, const Color &color);
	void DrawXYGrid(int startX, int startY, int endX, int endY, const Color &color);
	void DrawXZGrid(int width, int height, const Color &color);
	void DrawXZGrid(int startX, int startZ, int endX, int endZ, const Color &color);
	void DrawYZGrid(int width, int height, const Color &color);
	void DrawYZGrid(int startY, int startZ, int endY, int endZ, const Color &color);
	void DrawBox(const Vector3 &pos, const Vector3 &extents, const Color &color);
	void DrawSphere(const Vector3 &pos, float radius, int verticalSegments, int radialSegments, const Color &color);

	void FillTriangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color1, const Color &color2, const Color &color3);
	void FillQuad(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector3 &v4, const Color &color);
	void FillBox(const Vector3 &pos, const Vector3 &extents, const Color &color);
	void FillSphere(const Vector3 &pos, float radius, int verticalSegments, int radialSegments, const Color &color);
protected:
private:
	struct VertexPositionColor {
		Vector3 Position;
		Color Color;
	};

	// bufferSize must be a multiple of 6 to accomodate lines and triangles
	static const int bufferSize = 256 * 6;
	VertexPositionColor vertexBuffer[bufferSize];
	Matrix world;
	Matrix view;
	Matrix projection;
	GLuint vao;
	GLuint vbo;
	Shader shader;
	PrimitiveType primitiveType;
	bool hasBegun;
	unsigned int vertCounter;
};

}
