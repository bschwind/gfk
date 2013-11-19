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

Shader Shader::CreateFromFile(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName)
{
	std::string vertexShaderSource = GetShaderSource(vertexShaderFileName);
	std::string fragmentShaderSource = GetShaderSource(fragmentShaderFileName);

	return CreateFromStringSource(vertexShaderSource, fragmentShaderSource);
}

Shader Shader::CreateFromStringSource(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
	const char *vertexShaderStart = &vertexShaderSource[0];
	const char *fragmentShaderStart = &fragmentShaderSource[0];

	GLuint vertexShader = LoadAndCompileShader(vertexShaderStart, GL_VERTEX_SHADER);
	GLuint fragmentShader = LoadAndCompileShader(fragmentShaderStart, GL_FRAGMENT_SHADER);

	// Attach the above shader to a program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Flag the shaders for deletion
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Link and use the program
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	Shader returnShader;
	returnShader.Natives.OpenGL.ShaderID = shaderProgram;

	return returnShader;
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

}