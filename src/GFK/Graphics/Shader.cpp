#include <GFK/Graphics/Shader.hpp>
#include <GFK/System/Logger.hpp>
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
	glDeleteProgram(natives.OpenGL.ShaderID);
	GLErrorCheck();
}

void Shader::Apply()
{
	glUseProgram(natives.OpenGL.ShaderID);
	GLErrorCheck();
}

void Shader::CreateFromFile(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName)
{
	std::string vertexShaderSource = GetShaderSource(vertexShaderFileName);
	std::string fragmentShaderSource = GetShaderSource(fragmentShaderFileName);

	return CreateFromStringSource(vertexShaderSource, fragmentShaderSource);
}

void Shader::CreateFromStringSource(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
	natives.OpenGL.ShaderID = glCreateProgram();
	GLErrorCheck();

	const char *vertexShaderStart = &vertexShaderSource[0];
	const char *fragmentShaderStart = &fragmentShaderSource[0];

	GLuint vertexShader = LoadAndCompileShader(vertexShaderStart, GL_VERTEX_SHADER);
	GLuint fragmentShader = LoadAndCompileShader(fragmentShaderStart, GL_FRAGMENT_SHADER);

	// Attach the above shader to a program
	glAttachShader(natives.OpenGL.ShaderID, vertexShader);
	GLErrorCheck();
	glAttachShader(natives.OpenGL.ShaderID, fragmentShader);
	GLErrorCheck();

	// Flag the shaders for deletion
	glDeleteShader(vertexShader);
	GLErrorCheck();
	glDeleteShader(fragmentShader);
	GLErrorCheck();

	for (auto iter = GLSL_ATTRIB_MAP.begin(); iter != GLSL_ATTRIB_MAP.end(); iter++)
	{
		glBindAttribLocation(natives.OpenGL.ShaderID, iter->second, iter->first.c_str());
		GLErrorCheck();
	}

	// Link and use the program
	glLinkProgram(natives.OpenGL.ShaderID);
	GLErrorCheck();
	glUseProgram(natives.OpenGL.ShaderID);
	GLErrorCheck();

	BuildUniformMap(natives.OpenGL.ShaderID);
}

void Shader::BuildUniformMap(GLuint shaderID)
{
	GLint uniformCount = 0;

	glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &uniformCount);
	GLErrorCheck();

	int uniformNameLength = 0;
	int uniformSize = 0;
	GLenum uniformType = 0;
	char tempUniformName[256];

	for (int i = 0; i < uniformCount; i++)
	{
		glGetActiveUniform(shaderID, i, 256, &uniformNameLength, &uniformSize, &uniformType, tempUniformName);
		GLErrorCheck();
		GLint uniformLocation = glGetUniformLocation(shaderID, tempUniformName);
		GLErrorCheck();

		uniformMap[tempUniformName] = uniformLocation;
	}
}

GLuint Shader::LoadAndCompileShader(const char *source, GLenum shaderType)
{
	// Compile the shader
	GLuint shader = glCreateShader(shaderType);
	GLErrorCheck();
	glShaderSource(shader, 1, &source, NULL);
	GLErrorCheck();
	glCompileShader(shader);
	GLErrorCheck();

	// Check the result of the compilation
	GLint test;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
	GLErrorCheck();
	if (!test)
	{
		Logger::LogError("Shader compilation failed with this message:");
		std::vector<char> compilation_log(512);
		glGetShaderInfoLog(shader, compilation_log.size(), NULL, &compilation_log[0]);
		GLErrorCheck();
		Logger::LogError(std::string(&compilation_log[0]));

		exit(-1);
	}
	
	return shader;
}

std::string Shader::GetShaderSource(const std::string fileName)
{
	std::ifstream in;
	in.open(fileName, std::ios::binary);

	if (in.is_open())
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
		Logger::LogError(std::string("Unable to open ") + std::string(fileName));
		exit(-1);
	}

	return "";
}

void Shader::SetUniform(const std::string attribute, float value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform1f(uniformLocation, value);
	GLErrorCheck();
}

void Shader::SetUniform(const std::string attribute, const Vector2 &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform2f(uniformLocation, value.X, value.Y);
	GLErrorCheck();
}

void Shader::SetUniform(const std::string attribute, const Vector3 &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform3f(uniformLocation, value.X, value.Y, value.Z);
	GLErrorCheck();
}

void Shader::SetUniform(const std::string attribute, const Matrix &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniformMatrix4fv(uniformLocation, 1, false, value.ToFloatArray());
	GLErrorCheck();
}

void Shader::SetUniform(const std::string attribute, const Color &value)
{
	GLint uniformLocation = uniformMap.at(attribute);
	glUniform4f(uniformLocation, value.R, value.G, value.B, value.A);
	GLErrorCheck();
}

}