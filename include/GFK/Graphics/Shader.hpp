#pragma once

#include <GL/glew.h>
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

struct NativeVars
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
	static Shader CreateFromStringSource(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);

	NativeVars Natives;
protected:
private:
	static GLuint LoadAndCompileShader(const char *source, GLenum shaderType);
	static std::string GetShaderSource(const std::string fileName);
	static void BuildAttributeMap(GLuint shaderID);
};

}