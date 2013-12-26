#include <GFK/Graphics/PrimitiveBatch3D.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>
#include <cmath>

namespace gfk
{

PrimitiveBatch3D::PrimitiveBatch3D()
{
	vertCounter = 0;
}

PrimitiveBatch3D::~PrimitiveBatch3D()
{
	glDeleteVertexArrays(1, &vao);
}

void PrimitiveBatch3D::Initialize() {
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
	"in vec4 pos; "
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
	glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Position));
	glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, stride, (void *)offsetof(VertexPositionColor, Color));

	// Enable the attribute
	glEnableVertexAttribArray(positionAttribute);
	glEnableVertexAttribArray(colorAttribute);

	// Bind to 0 so we don't inadvertently record any more GL operations on the VAO
	glBindVertexArray(0);
}

void PrimitiveBatch3D::Begin(PrimitiveType primitiveType)
{
	this->primitiveType = primitiveType;

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

	// Copy our vertex data from CPU to GPU
	// Consider "double buffering" the vertex data for performance,
	// if it comes to that.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertCounter * sizeof(VertexPositionColor), vertexBuffer);
	glEnable(GL_DEPTH_TEST);

	shader.Apply();

	// Matrix world = Matrix::CreateTranslation(Vector3(0, 0, 0)) * Matrix::CreateRotationZ(MathHelper::Pi * 0.25f);
	Matrix world = Matrix::Identity;
	Matrix view = Matrix::CreateLookAt(Vector3(0, 0, 100), Vector3(0, 0, 0), Vector3::Up);
	// Matrix proj = Matrix::CreateOrthographic(1280, 720, 0.1f, 100);
	Matrix proj = Matrix::CreatePerspectiveFieldOfView(MathHelper::Pi * 0.25f, 1280.0f / 720.0f, 0.1f, 1000.0f);

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

// void PrimitiveBatch3D::Draw2DGrid(int width, int height, const Color &color)
// {
// 	for (int x = 0; x <= width; x++)
// 	{
// 		DrawLine(Vector3(x, 0), Vector3(x, height), color, color);
// 	}

// 	for (int y = 0; y <= height; y++)
// 	{
// 		DrawLine(Vector3(0, y), Vector3(width, y), color, color);
// 	}
// }

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
