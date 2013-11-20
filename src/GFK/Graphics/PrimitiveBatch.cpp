#include <GFK/Graphics/PrimitiveBatch.hpp>
#include <iostream>

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
	std::string vertShaderSource = "#version 150\nin vec4 position;\nvoid main() {\ngl_Position = position;\n}\n";
	std::string fragShaderSource = "#version 150\nout vec4 out_color;\nvoid main() {\nout_color = vec4(1.0, 1.0, 1.0, 1.0);\n}\n";

	Shader shader = Shader::CreateFromStringSource(vertShaderSource, fragShaderSource);

	// Get the location of the attributes that enter into the vertex shader
	GLint position_attribute = glGetAttribLocation(shader.Natives.OpenGL.ShaderID, "position");

	// Specify how the data for position can be accessed
	glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable the attribute
	glEnableVertexAttribArray(position_attribute);
}

void PrimitiveBatch::Begin()
{
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

	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, vertCounter / 2);

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