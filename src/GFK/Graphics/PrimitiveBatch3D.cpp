#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>
#include <cmath>
#include <GFK/System/Logger.hpp>

namespace gfk
{

PrimitiveBatch3D::PrimitiveBatch3D() :
hasBegun(false),
vertCounter(0)
{
	
}

PrimitiveBatch3D::~PrimitiveBatch3D()
{
#if !defined(PLATFORM_ANDROID)
	glDeleteVertexArrays(1, &vao);
	GLErrorCheck();
#endif
	glDeleteBuffers(1, &vbo);
	GLErrorCheck();
}

void PrimitiveBatch3D::Initialize() {
#if !defined(PLATFORM_ANDROID)
	// Use a Vertex Array Object
	glGenVertexArrays(1, &vao);
	GLErrorCheck();
	glBindVertexArray(vao);
	GLErrorCheck();
#endif

	// Create a Vertex Buffer Object that will store the vertices on video memory
	glGenBuffers(1, &vbo);
	GLErrorCheck();

	// Allocate space and upload the data from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLErrorCheck();
	glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(VertexPositionColor), vertexBuffer, GL_DYNAMIC_DRAW);
	GLErrorCheck();

	InitializeShader();

	BindAttributes();

#if !defined(PLATFORM_ANDROID)
	// Bind to 0 so we don't inadvertently record any more GL operations on the VAO
	glBindVertexArray(0);
	GLErrorCheck();
#endif
}

void PrimitiveBatch3D::InitializeShader()
{
#if !defined(PLATFORM_ANDROID)
	// A simple vertex and fragment shader. The vertex shader just passes the position and color through
	// The fragment shader just returns the color from the vertex shader
	std::string vertShaderSource =
	"#version 150\n"
	"uniform mat4 world; "
	"uniform mat4 view; "
	"uniform mat4 proj; "
	"in vec4 position; "
	"in vec4 color; "
	"out vec4 vertColor; "
	"void main() "
	"{ "
		"gl_Position = proj * (view * (world * position)); "
		"vertColor = color; "
	"}";
	
	std::string fragShaderSource =
	"#version 150\n"
	"in vec4 vertColor; "
	"in vec4 pos; "
	"out vec4 out_color; "
	"void main() "
	"{ "
		"out_color = vertColor; "
	"}";
#else
	// A simple vertex and fragment shader. The vertex shader just passes the position and color through
	// The fragment shader just returns the color from the vertex shader
	std::string vertShaderSource =
	"uniform mat4 world; "
	"uniform mat4 view; "
	"uniform mat4 proj; "
	"attribute vec4 position; "
	"attribute vec4 color; "
	"varying vec4 vertColor; "
	"void main() "
	"{ "
		"gl_Position = proj * (view * (world * position)); "
		"vertColor = color; "
	"}";
	
	std::string fragShaderSource =
	"precision mediump float;\n"
	"varying vec4 vertColor; "
	"void main() "
	"{ "
		"gl_FragColor = vertColor; "
	"}";
#endif

	shader.CreateFromStringSource(vertShaderSource, fragShaderSource);
}

void PrimitiveBatch3D::BindAttributes()
{
	int stride = sizeof(VertexPositionColor);

	// Specify how the data for position can be accessed
	glVertexAttribPointer(GLSL_ATTRIB_MAP["position"], 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Position));
	GLErrorCheck("position");
	glVertexAttribPointer(GLSL_ATTRIB_MAP["color"], 4, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Color));
	GLErrorCheck("color");

	// Enable the attribute
	glEnableVertexAttribArray(GLSL_ATTRIB_MAP["position"]);
	GLErrorCheck("position again");
	glEnableVertexAttribArray(GLSL_ATTRIB_MAP["color"]);
	GLErrorCheck("color again");
}

void PrimitiveBatch3D::Begin(PrimitiveType primitiveType, Camera &camera)
{
	Begin(primitiveType, camera.GetView(), camera.GetProjection(), Matrix::Identity);
}

void PrimitiveBatch3D::Begin(PrimitiveType primitiveType, Camera &camera, const Matrix &worldMatrix)
{
	Begin(primitiveType, camera.GetView(), camera.GetProjection(), worldMatrix);
}

void PrimitiveBatch3D::Begin(PrimitiveType primitiveType, const Matrix &view, const Matrix &projection)
{
	Begin(primitiveType, view, projection, Matrix::Identity);
}

void PrimitiveBatch3D::Begin(PrimitiveType primitiveType, const Matrix &view, const Matrix &projection, const Matrix &worldMatrix)
{
	this->primitiveType = primitiveType;
	world = worldMatrix;
	this->view = view;
	this->projection = projection;

	if (hasBegun)
	{
		// throw error
		return;
	}

	hasBegun = true;
}

void PrimitiveBatch3D::Flush()
{
	if (vertCounter <= 0)
	{
		return;
	}

	shader.Apply();

	// Copy our vertex data from CPU to GPU
	// Consider "double buffering" the vertex data for performance,
	// if it comes to that.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLErrorCheck("bind buffer VBO");
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertCounter * sizeof(VertexPositionColor), vertexBuffer);
	GLErrorCheck("buffer sub data ");
	glEnable(GL_DEPTH_TEST);
	GLErrorCheck("enable depth test");

	shader.SetUniform("world", world);
	shader.SetUniform("view", view);
	shader.SetUniform("proj", projection);

#if !defined(PLATFORM_ANDROID)
	glBindVertexArray(vao);
	GLErrorCheck();
#else
	BindAttributes();
	GLErrorCheck("empty bind attributes");
#endif

	int primitiveMode = GL_LINES;
	if (primitiveType == PrimitiveType::TriangleList)
	{
		primitiveMode = GL_TRIANGLES;
	}

	glDrawArrays(primitiveMode, 0, vertCounter);
	GLErrorCheck("draw arrays");

	vertCounter = 0;
}

void PrimitiveBatch3D::DrawMesh(const Mesh &mesh)
{
	shader.Apply();
	mesh.Bind();
	glEnable(GL_DEPTH_TEST);
	GLErrorCheck();

	shader.SetUniform("world", world);
	shader.SetUniform("view", view);
	shader.SetUniform("proj", projection);

	glDrawArrays(GL_TRIANGLES, 0, mesh.numVertices);
	GLErrorCheck();

	mesh.Unbind();
}

void PrimitiveBatch3D::End()
{
	if (!hasBegun)
	{
		// throw error
		return;
	}

	Flush();

	hasBegun = false;
}

void PrimitiveBatch3D::AddVertex(const Vector3 &vertex, const Color &color)
{
	if (!hasBegun)
	{
		// throw error
		return;
	}
	if (vertCounter >= bufferSize)
	{
		Flush();
	}

	VertexPositionColor vert;
	vert.Position = vertex;
	vert.Color = color;

	vertexBuffer[vertCounter] = vert;

	vertCounter++;
}

void PrimitiveBatch3D::DrawLine(const Vector3 &v1, const Vector3 &v2, const Color &color1, const Color &color2)
{
	AddVertex(v1, color1);
	AddVertex(v2, color2);
}

void PrimitiveBatch3D::DrawTriangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color1, const Color &color2, const Color &color3)
{
	AddVertex(v1, color1);
	AddVertex(v2, color2);

	AddVertex(v2, color2);
	AddVertex(v3, color3);

	AddVertex(v3, color3);
	AddVertex(v1, color1);
}

void PrimitiveBatch3D::DrawQuad(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector3 &v4, const Color &color)
{
	AddVertex(v1, color);
	AddVertex(v2, color);

	AddVertex(v2, color);
	AddVertex(v3, color);

	AddVertex(v3, color);
	AddVertex(v4, color);

	AddVertex(v4, color);
	AddVertex(v1, color);
}

void PrimitiveBatch3D::DrawXYGrid(int width, int height, const Color &color)
{
	for (int x = 0; x <= width; x++)
	{
		DrawLine(Vector3(x, 0, 0), Vector3(x, height, 0), color, color);
	}

	for (int y = 0; y <= height; y++)
	{
		DrawLine(Vector3(0, y, 0), Vector3(width, y, 0), color, color);
	}
}

void PrimitiveBatch3D::DrawXYGrid(int startX, int startY, int endX, int endY, const Color &color)
{
	for (int x = startX; x <= endX; x++)
	{
		DrawLine(Vector3(x, startY, 0), Vector3(x, endY, 0), color, color);
	}

	for (int y = startY; y <= endX; y++)
	{
		DrawLine(Vector3(startX, y, 0), Vector3(endX, y, 0), color, color);
	}
}

void PrimitiveBatch3D::DrawXZGrid(int width, int depth, const Color &color)
{
	for (int x = 0; x <= width; x++)
	{
		DrawLine(Vector3(x, 0, 0), Vector3(x, 0, depth), color, color);
	}

	for (int z = 0; z <= depth; z++)
	{
		DrawLine(Vector3(0, 0, z), Vector3(width, 0, z), color, color);
	}
}

void PrimitiveBatch3D::DrawXZGrid(int startX, int startZ, int endX, int endZ, const Color &color)
{
	for (int x = startX; x <= endX; x++)
	{
		DrawLine(Vector3(x, 0, startZ), Vector3(x, 0, endZ), color, color);
	}

	for (int z = startZ; z <= endZ; z++)
	{
		DrawLine(Vector3(startX, 0, z), Vector3(endX, 0, z), color, color);
	}
}

void PrimitiveBatch3D::DrawYZGrid(int height, int depth, const Color &color)
{
	for (int y = 0; y <= height; y++)
	{
		DrawLine(Vector3(0, y, 0), Vector3(0, y, depth), color, color);
	}

	for (int z = 0; z <= depth; z++)
	{
		DrawLine(Vector3(0, 0, z), Vector3(0, height, z), color, color);
	}
}

void PrimitiveBatch3D::DrawYZGrid(int startY, int startZ, int endY, int endZ, const Color &color)
{
	for (int y = startY; y <= endY; y++)
	{
		DrawLine(Vector3(0, y, startZ), Vector3(0, y, endZ), color, color);
	}

	for (int z = startZ; z <= endZ; z++)
	{
		DrawLine(Vector3(0, startY, z), Vector3(0, endY, z), color, color);
	}
}

void PrimitiveBatch3D::DrawBox(const Vector3 &pos, const Vector3 &extents, const Color &color)
{
	// Top
	DrawLine(
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		color,
		color);

	// Sides
	DrawLine(
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		color,
		color);

	// Bottom
	DrawLine(
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		color,
		color);
	DrawLine(
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		color,
		color);
}

void PrimitiveBatch3D::DrawSphere(const Vector3 &pos, float radius, int verticalSegments, int radialSegments, const Color &color)
{
	for (int i = 0; i < verticalSegments; i++)
	{
		float bodyAngle = ((float)i / verticalSegments) * MathHelper::Pi;
		float nextBodyAngle = ((float)(i+1) / verticalSegments) * MathHelper::Pi;

		for (int j = 0; j < radialSegments; j++)
		{
			float radialAngle = ((float)j / radialSegments) * MathHelper::TwoPi;
			float nextRadialAngle = ((float)(j+1) / radialSegments) * MathHelper::TwoPi;

			Vector3 v1 = Vector3(radius * (float)(cos(radialAngle) * sin(bodyAngle)), radius * (float)cos(bodyAngle), radius * (float)(sin(-radialAngle) * sin(bodyAngle)));
			Vector3 v2 = Vector3(radius * (float)(cos(nextRadialAngle) * sin(bodyAngle)), radius * (float)cos(bodyAngle), radius * (float)(sin(-nextRadialAngle) * sin(bodyAngle)));
			Vector3 v3 = Vector3(radius * (float)(cos(nextRadialAngle) * sin(nextBodyAngle)), radius * (float)cos(nextBodyAngle), radius * (float)(sin(-nextRadialAngle) * sin(nextBodyAngle)));
			Vector3 v4 = Vector3(radius * (float)(cos(radialAngle) * sin(nextBodyAngle)), radius * (float)cos(nextBodyAngle), radius * (float)(sin(-radialAngle) * sin(nextBodyAngle)));

			DrawQuad(pos + v1, pos + v2, pos + v3, pos + v4, color);
		}
	}
}

void PrimitiveBatch3D::FillTriangle(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Color &color1, const Color &color2, const Color &color3)
{
	AddVertex(v1, color1);
	AddVertex(v2, color2);
	AddVertex(v3, color3);
}

void PrimitiveBatch3D::FillQuad(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, const Vector3 &v4, const Color &color)
{
	FillTriangle(v1, v2, v4, color, color, color);
	FillTriangle(v2, v3, v4, color, color, color);
}

void PrimitiveBatch3D::FillBox(const Vector3 &pos, const Vector3 &extents, const Color &color)
{
	FillQuad(
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		color); // Top

	FillQuad(
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		color); // Front

	FillQuad(
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		color); // Left

	FillQuad(
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X - extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		color); // Back

	FillQuad(
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z + extents.Z),
		Vector3(pos.X + extents.X, pos.Y + extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		color); // Right

	FillQuad(
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z + extents.Z),
		Vector3(pos.X + extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		Vector3(pos.X - extents.X, pos.Y - extents.Y, pos.Z - extents.Z),
		color); // Bottom
}

void PrimitiveBatch3D::FillSphere(const Vector3 &pos, float radius, int verticalSegments, int radialSegments, const Color &color)
{
	for (int i = 0; i < verticalSegments; i++)
	{
		float bodyAngle = ((float)i / verticalSegments) * MathHelper::Pi;
		float nextBodyAngle = ((float)(i+1) / verticalSegments) * MathHelper::Pi;

		for (int j = 0; j < radialSegments; j++)
		{
			float radialAngle = ((float)j / radialSegments) * MathHelper::TwoPi;
			float nextRadialAngle = ((float)(j+1) / radialSegments) * MathHelper::TwoPi;

			Vector3 v1 = Vector3(radius * (float)(cos(radialAngle) * sin(bodyAngle)), radius * (float)cos(bodyAngle), radius * (float)(sin(-radialAngle) * sin(bodyAngle)));
			Vector3 v2 = Vector3(radius * (float)(cos(nextRadialAngle) * sin(bodyAngle)), radius * (float)cos(bodyAngle), radius * (float)(sin(-nextRadialAngle) * sin(bodyAngle)));
			Vector3 v3 = Vector3(radius * (float)(cos(nextRadialAngle) * sin(nextBodyAngle)), radius * (float)cos(nextBodyAngle), radius * (float)(sin(-nextRadialAngle) * sin(nextBodyAngle)));
			Vector3 v4 = Vector3(radius * (float)(cos(radialAngle) * sin(nextBodyAngle)), radius * (float)cos(nextBodyAngle), radius * (float)(sin(-radialAngle) * sin(nextBodyAngle)));

			FillQuad(pos + v1, pos + v2, pos + v3, pos + v4, color);
		}
	}
}

}
