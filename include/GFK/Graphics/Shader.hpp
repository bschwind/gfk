#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GFK/Math/Vector2.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Graphics/Color.hpp>
#include <string>
#include <vector>
#include <map>

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
	void CreateFromFile(const std::string &vertexShaderFileName, const std::string &fragmentShaderFileName);
	void CreateFromStringSource(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
	void SetUniform(std::string attribute, float value);
	void SetUniform(std::string attribute, Vector2 value);
	void SetUniform(std::string attribute, Vector3 value);
	void SetUniform(std::string attribute, Color value);

	NativeVars Natives;
protected:
private:
	static GLuint LoadAndCompileShader(const char *source, GLenum shaderType);
	static std::string GetShaderSource(const std::string fileName);

	void BuildUniformMap(GLuint shaderID);

	std::map<std::string, GLuint> uniformMap;
};

}