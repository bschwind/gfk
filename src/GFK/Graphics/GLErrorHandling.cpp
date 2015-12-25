#include <GFK/Graphics/GLHeader.hpp>
#include <GFK/System/Logger.hpp>
#include <iostream>
#include <sstream>

namespace gfk
{

bool GLErrorCheck()
{
	return GLErrorCheck("");
}

bool GLErrorCheck(const std::string &tag)
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		Logger::Log("OpenGL error detected: \n");
		Logger::Logf("Tag: %s", tag.c_str());
		Logger::Log("\tError: \n");

		switch (error)
		{
		case GL_INVALID_ENUM:
			Logger::Log("GL_INVALID_ENUM\n");
			break;
		case GL_INVALID_VALUE:
			Logger::Log("GL_INVALID_VALUE\n");
			break;
		case GL_INVALID_OPERATION:
			Logger::Log("GL_INVALID_OPERATION\n");
			break;
	#if !defined(PLATFORM_ANDROID)
		case GL_STACK_UNDERFLOW:
			Logger::Log("GL_STACK_UNDERFLOW\n");
			break;
		case GL_STACK_OVERFLOW:
			Logger::Log("GL_STACK_OVERFLOW\n");
			break;
	#endif
		case GL_OUT_OF_MEMORY:
			Logger::Log("GL_OUT_OF_MEMORY\n");
			break;
		default:
			Logger::Logf("Something Else(%u)\n", error);
		}

		std::cout << std::endl;
		return true;
	}

	return false;
}
}
