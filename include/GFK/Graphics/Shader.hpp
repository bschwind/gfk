#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace gfk
{

class Shader
{
public:
	Shader();
	Shader(GLuint shaderID);
	~Shader();

	void Apply();
	static Shader CreateFromFile(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName);
	GLuint GetGLShaderID();
protected:
private:
	GLuint shaderID;
	static GLuint LoadAndCompileShader(const std::string fileName, GLenum shaderType);
	static void ReadShaderSource(const std::string fileName, std::vector<char> &buffer);
};

}