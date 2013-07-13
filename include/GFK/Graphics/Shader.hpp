#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>

namespace gfk
{

struct GL
{
	GLuint ShaderID;
};

// struct DirectX
// {
	
// };

struct Natives
{
	GL OpenGL;
};

class Shader
{
public:
	Shader();
	~Shader();

	void Apply();
	static Shader CreateFromFile(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName);

	Natives Natives;
protected:
private:
	static GLuint LoadAndCompileShader(const std::string fileName, GLenum shaderType);
	static void ReadShaderSource(const std::string fileName, std::vector<char> &buffer);
};

}