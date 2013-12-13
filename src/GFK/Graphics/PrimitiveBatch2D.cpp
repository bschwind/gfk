#include <GFK/Graphics/PrimitiveBatch2D.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>
#include <cmath>

namespace gfk
{

PrimitiveBatch2D::PrimitiveBatch2D()
{
	vertCounter = 0;
}

PrimitiveBatch2D::~PrimitiveBatch2D()
{
	glDeleteVertexArrays(1, &vao);
}

void PrimitiveBatch2D::Initialize() {
	// Use a Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object that will store the vertices on video memory
	glGenBuffers(1, &vbo);

	// Allocate space and upload the data from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_DYNAMIC_DRAW);

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
	"out vec4 out_color; "
	"void main() "
	"{ "
		"out_color = vertColor; "
	"}";

	shader.CreateFromStringSource(vertShaderSource, fragShaderSource);

	// Get the location of the attributes that enter into the vertex shader
	GLint positionAttribute = glGetAttribLocation(shader.Natives.OpenGL.ShaderID, "position");
	GLint colorAttribute = glGetAttribLocation(shader.Natives.OpenGL.ShaderID, "color");

	int stride = sizeof(VertexPositionColor);

	// Specify how the data for position can be accessed
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Position));
	glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Color));

	// Enable the attribute
	glEnableVertexAttribArray(positionAttribute);
	glEnableVertexAttribArray(colorAttribute);

	// Bind to 0 so we don't inadvertently record any more GL operations on the VAO
	glBindVertexArray(0);
}

void PrimitiveBatch2D::Begin(PrimitiveType primitiveType)
{
	this->primitiveType = primitiveType;

	if (hasBegun)
	{
		// throw error
		return;
	}

	hasBegun = true;
}

void PrimitiveBatch2D::Flush()
{
	if (vertCounter <= 0)
	{
		return;
	}

	// Copy our vertex data from CPU to GPU
	// Consider "double buffering" the vertex data for performance,
	// if it comes to that.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertCounter * sizeof(VertexPositionColor), vertexBuffer);

	shader.Apply();

	Matrix world = Matrix::CreateTranslation(Vector3(0, 0, 0));
	Matrix view = Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, -1), Vector3::Up);
	Matrix proj = Matrix::CreateOrthographic(100, 100, 0.1f, 100);

	shader.SetUniform("world", world);
	shader.SetUniform("view", view);
	shader.SetUniform("proj", proj);

	glBindVertexArray(vao);

	int primitiveMode = GL_LINES;
	if (primitiveType == PrimitiveType::TriangleList)
	{
		primitiveMode = GL_TRIANGLES;
	}

	glDrawArrays(primitiveMode, 0, vertCounter);

	vertCounter = 0;
}

void PrimitiveBatch2D::End()
{
	if (!hasBegun)
	{
		// throw error
		return;
	}

	Flush();

	hasBegun = false;
}

void PrimitiveBatch2D::AddVertex(const Vector2 &vertex, const Color &color)
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

void PrimitiveBatch2D::DrawLine(const Vector2 &v1, const Vector2 &v2, const Color &color1, const Color &color2)
{
	AddVertex(v1, color1);
	AddVertex(v2, color2);
}

void PrimitiveBatch2D::DrawTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Color &color1, const Color &color2, const Color &color3)
{
	AddVertex(v1, color1);
	AddVertex(v2, color2);

	AddVertex(v2, color2);
	AddVertex(v3, color3);

	AddVertex(v3, color3);
	AddVertex(v1, color1);
}

void PrimitiveBatch2D::DrawCircle(const Vector2 &center, float radius, int segments, const Color &color)
{
	for (int i = 0; i < segments; i++)
	{
		float angle = ((float)i / segments) * MathHelper::TwoPi;
		float nextAngle = ((float)(i+1) / segments) * MathHelper::TwoPi;
		Vector2 pos = center + Vector2((float)cos(angle) * radius, (float)sin(angle) * radius);
		Vector2 nextPos = center + Vector2((float)cos(nextAngle) * radius, (float)sin(nextAngle) * radius);
		AddVertex(pos, color);
		AddVertex(nextPos, color);
	}
}

void PrimitiveBatch2D::DrawPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments, const Color &color)
{
	AddVertex(center, color);
	AddVertex(center + Vector2((float)cos(startAngle), (float)sin(startAngle)) * radius, color);

	float delta = fabs(endAngle - startAngle) / segments;

	for (int i = 0; i < segments; i++)
	{
		float start = startAngle + (i * delta);
		float end = startAngle + ((i + 1) * delta);
		AddVertex(center + Vector2((float)cos(start), (float)sin(start)) * radius, color);
		AddVertex(center + Vector2((float)cos(end), (float)sin(end)) * radius, color);
	}

	AddVertex(center + Vector2((float)cos(endAngle), (float)sin(endAngle)) * radius, color);
	AddVertex(center, color);
}

void PrimitiveBatch2D::Draw2DGrid(int width, int height, const Color &color)
{
	for (int x = 0; x <= width; x++)
	{
		DrawLine(Vector2(x, 0), Vector2(x, height), color, color);
	}

	for (int y = 0; y <= height; y++)
	{
		DrawLine(Vector2(0, y), Vector2(width, y), color, color);
	}
}

void PrimitiveBatch2D::FillTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Color &color1, const Color &color2, const Color &color3)
{
	AddVertex(v1, color1);
	AddVertex(v2, color2);
	AddVertex(v3, color3);
}

void PrimitiveBatch2D::FillQuad(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Vector2 &v4, const Color &color)
{
	FillTriangle(v1, v2, v4, color, color, color);
	FillTriangle(v2, v3, v4, color, color, color);
}

void PrimitiveBatch2D::FillCircle(const Vector2 &center, float radius, int segments, const Color &color)
{
	float startAngle = 0.0f;
	float endAngle = MathHelper::TwoPi;
	float delta = fabs(endAngle - startAngle) / segments;

	for (int i = 0; i < segments; i++)
	{
		float start = startAngle + (i * delta);
		float end = startAngle + ((i + 1) * delta);

		FillTriangle(
			center,
			center + Vector2((float)cos(end) * radius, (float)sin(end) * radius),
			center + Vector2((float)cos(start) * radius, (float)sin(start) * radius),
			color,
			color,
			color);
	}
}

void PrimitiveBatch2D::FillPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments, const Color &color)
{
	float delta = fabs(endAngle - startAngle) / segments;

	for (int i = 0; i < segments; i++)
	{
		float start = startAngle + (i * delta);
		float end = startAngle + ((i + 1) * delta);

		FillTriangle(
			center,
			center + Vector2((float)cos(end) * radius, (float)sin(end) * radius),
			center + Vector2((float)cos(start) * radius, (float)sin(start) * radius),
			color,
			color,
			color);
	}
}

}
