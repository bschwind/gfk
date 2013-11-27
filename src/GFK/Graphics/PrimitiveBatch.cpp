#include <GFK/Graphics/PrimitiveBatch.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>
#include <cmath>

namespace gfk
{

PrimitiveBatch::PrimitiveBatch()
{
	vertCounter = 0;
}

PrimitiveBatch::~PrimitiveBatch()
{
	glDeleteVertexArrays(1, &vao);
}

void PrimitiveBatch::Initialize() {
	// Use a Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object that will store the vertices on video memory
	glGenBuffers(1, &vbo);

	// Allocate space and upload the data from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_DYNAMIC_DRAW);

	// A simple vertex and fragment shader. The vertex shader just passes the position through
	// The fragment shader just returns white
	std::string vertShaderSource = "#version 150\n uniform mat4 world; uniform mat4 view; uniform mat4 proj;\nin vec4 position;\nvoid main() {\ngl_Position = proj * (view * (world * position));\n}\n";
	std::string fragShaderSource = "#version 150\nuniform vec4 lineColor;\nout vec4 out_color;\nvoid main() {\nout_color = lineColor;\n}\n";

	shader.CreateFromStringSource(vertShaderSource, fragShaderSource);

	// Get the location of the attributes that enter into the vertex shader
	GLint position_attribute = glGetAttribLocation(shader.Natives.OpenGL.ShaderID, "position");

	// Specify how the data for position can be accessed
	glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable the attribute
	glEnableVertexAttribArray(position_attribute);

	// ?
	glBindVertexArray(vao);
}

void PrimitiveBatch::Begin(PrimitiveType primitiveType)
{
	this->primitiveType = primitiveType;

	if (hasBegun)
	{
		// throw error
		return;
	}

	hasBegun = true;
}

void PrimitiveBatch::AddVertex(const Vector2 &vertex)
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

	vertexBuffer[vertCounter] = vertex.X;
	vertexBuffer[vertCounter + 1] = vertex.Y;

	vertCounter += 2;
}

void PrimitiveBatch::DrawLine(const Vector2 &v1, const Vector2 &v2)
{
	AddVertex(v1);
	AddVertex(v2);
}

void PrimitiveBatch::DrawTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3)
{
	AddVertex(v1);
	AddVertex(v2);
	AddVertex(v2);
	AddVertex(v3);
	AddVertex(v3);
	AddVertex(v1);
}

void PrimitiveBatch::DrawCircle(const Vector2 &center, float radius, int segments)
{
	for (int i = 0; i < segments; i++)
	{
		float angle = ((float)i / segments) * MathHelper::TwoPi;
		float nextAngle = ((float)(i+1) / segments) * MathHelper::TwoPi;
		Vector2 pos = center + Vector2((float)cos(angle) * radius, (float)sin(angle) * radius);
		Vector2 nextPos = center + Vector2((float)cos(nextAngle) * radius, (float)sin(nextAngle) * radius);
		AddVertex(pos);
		AddVertex(nextPos);
	}
}

void PrimitiveBatch::DrawPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments)
{
	AddVertex(center);
	AddVertex(center + Vector2((float)cos(startAngle), (float)sin(startAngle)) * radius);

	float delta = fabs(endAngle - startAngle) / segments;

	for (int i = 0; i < segments; i++)
	{
		float start = startAngle + (i * delta);
		float end = startAngle + ((i + 1) * delta);
		AddVertex(center + Vector2((float)cos(start), (float)sin(start)) * radius);
		AddVertex(center + Vector2((float)cos(end), (float)sin(end)) * radius);
	}

	AddVertex(center + Vector2((float)cos(endAngle), (float)sin(endAngle)) * radius);
	AddVertex(center);
}

void PrimitiveBatch::Draw2DGrid(int width, int height)
{
	for (int x = 0; x <= width; x++)
	{
		DrawLine(Vector2(x, 0), Vector2(x, height));
	}

	for (int y = 0; y <= height; y++)
	{
		DrawLine(Vector2(0, y), Vector2(width, y));
	}
}

void PrimitiveBatch::FillTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3)
{
	AddVertex(v1);
	AddVertex(v2);
	AddVertex(v3);
}

void PrimitiveBatch::FillQuad(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, const Vector2 &v4)
{
	FillTriangle(v1, v2, v4);
	FillTriangle(v2, v3, v4);
}

void PrimitiveBatch::FillCircle(const Vector2 &center, float radius, int segments)
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
			center + Vector2((float)cos(start) * radius, (float)sin(start) * radius));
	}
}

void PrimitiveBatch::FillPie(const Vector2 &center, float radius, float startAngle, float endAngle, int segments)
{
	float delta = fabs(endAngle - startAngle) / segments;

	for (int i = 0; i < segments; i++)
	{
		float start = startAngle + (i * delta);
		float end = startAngle + ((i + 1) * delta);

		FillTriangle(
			center,
			center + Vector2((float)cos(end) * radius, (float)sin(end) * radius),
			center + Vector2((float)cos(start) * radius, (float)sin(start) * radius));
	}
}

void PrimitiveBatch::Flush()
{
	if (vertCounter <= 0)
	{
		return;
	}

	// Copy our vertex data from CPU to GPU
	// Consider "double buffering" the vertex data for performance,
	// if it comes to that.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertCounter * sizeof(GLfloat), vertexBuffer);

	shader.Apply();

	shader.SetUniform("view", Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, -1), Vector3::Up));
	Matrix proj = Matrix::CreateOrthographic(100, 100, 0.1, 100);
	shader.SetUniform("proj", proj);

	Matrix world = Matrix::CreateTranslation(Vector3(0, 0, 0));

	shader.SetUniform("world", world);
	shader.SetUniform("lineColor", Color::Green);

	glBindVertexArray(vao);

	int primitiveMode = GL_LINES;
	if (primitiveType == PrimitiveType::TriangleList)
	{
		primitiveMode = GL_TRIANGLES;
	}

	// Later, we will divided by 3 instead of 2, for 3D positions
	glDrawArrays(primitiveMode, 0, vertCounter / 2);

	vertCounter = 0;
}

void PrimitiveBatch::End()
{
	if (!hasBegun)
	{
		// throw error
		return;
	}

	Flush();

	hasBegun = false;
}

}