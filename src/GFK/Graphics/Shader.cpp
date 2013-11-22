#include <GFK/Graphics/Shader.hpp>
#include <iostream>
#include <cstdlib>
#include <fstream>

namespace gfk
{

Shader::Shader()
{

}

Shader::~Shader()
{
	glDeleteProgram(Natives.OpenGL.ShaderID);
}

void Shader::Apply()
{
	glUseProgram(Natives.OpenGL.ShaderID);
}

void Shader::CreateFromFile(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName)
{
	std::string vertexShaderSource = GetShaderSource(vertexShaderFileName);
	std::string fragmentShaderSource = GetShaderSource(fragmentShaderFileName);

	return CreateFromStringSource(vertexShaderSource, fragmentShaderSource);
}

void Shader::CreateFromStringSource(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
	Natives.OpenGL.ShaderID = glCreateProgram();

	const char *vertexShaderStart = &vertexShaderSource[0];
	const char *fragmentShaderStart = &fragmentShaderSource[0];

	GLuint vertexShader = LoadAndCompileShader(vertexShaderStart, GL_VERTEX_SHADER);
	GLuint fragmentShader = LoadAndCompileShader(fragmentShaderStart, GL_FRAGMENT_SHADER);

	// Attach the above shader to a program
	glAttachShader(Natives.OpenGL.ShaderID, vertexShader);
	glAttachShader(Natives.OpenGL.ShaderID, fragmentShader);

	// Flag the shaders for deletion
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Link and use the program
	glLinkProgram(Natives.OpenGL.ShaderID);
	glUseProgram(Natives.OpenGL.ShaderID);

	BuildUniformMap(Natives.OpenGL.ShaderID);
}

void Shader::BuildUniformMap(GLuint shaderID)
{
	GLint uniformCount = 0;

	glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &uniformCount);

	int uniformNameLength = 0;
	int uniformSize = 0;
	GLenum uniformType = 0;
	char tempUniformName[256];

	for (int i = 0; i < uniformCount; i++)
	{
		glGetActiveUniform(shaderID, i, 256, &uniformNameLength, &uniformSize, &uniformType, tempUniformName);
		GLint uniformLocation = glGetUniformLocation(shaderID, tempUniformName);

		uniformMap[tempUniformName] = uniformLocation;
	}
}

GLuint Shader::LoadAndCompileShader(const char *source, GLenum shaderType)
{
	// Compile the shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	// Check the result of the compilation
	GLint test;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
	if (!test)
	{
		std::cerr << "Shader compilation failed with this message:" << std::endl;
		std::vector<char> compilation_log(512);
		glGetShaderInfoLog(shader, compilation_log.size(), NULL, &compilation_log[0]);
		std::cerr << &compilation_log[0] << std::endl;

		exit(-1);
	}
	
	return shader;
}

std::string Shader::GetShaderSource(const std::string fileName)
{
	std::ifstream in;
	in.open(fileName, std::ios::binary);

	if(in.is_open())
	{
		std::string fileContents;
		// Get the number of bytes stored in this file
		in.seekg(0, std::ios::end);
		size_t length = (size_t)in.tellg();

		// Go to start of the file
		in.seekg(0, std::ios::beg);

		// Read the content of the file in a buffer
		fileContents.resize(length);
		in.read(&fileContents[0], length);
		in.close();

		return fileContents;
	}
	else
	{
		std::cerr << "Unable to open " << fileName << " I'm out!" << std::endl;
		exit(-1);
	}

	return "";
}

void Shader::SetUniform(const std::string attribute, float value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform1f(uniformLocation, value);
}

void Shader::SetUniform(const std::string attribute, const Vector2 &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform2f(uniformLocation, value.X, value.Y);
}

void Shader::SetUniform(const std::string attribute, const Vector3 &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform3f(uniformLocation, value.X, value.Y, value.Z);
}

void Shader::SetUniform(const std::string attribute, const Matrix &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniformMatrix4fv(uniformLocation, 1, false, value.ToFloatArray());
}

void Shader::SetUniform(const std::string attribute, const Color &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform4f(uniformLocation, value.R, value.G, value.B, value.A);
}

}