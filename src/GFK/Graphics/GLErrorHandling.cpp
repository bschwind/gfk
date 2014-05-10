#include <GFK/Graphics/GLHeader.hpp>
#include <GFK/System/Logger.hpp>
#include <iostream>
#include <sstream>

namespace gfk
{

bool GLErrorCheck()
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		Logger::Log("OpenGL error detected: ");
		Logger::Log("\tError: ");

		switch (error)
		{
		case GL_INVALID_ENUM:
			Logger::Log("GL_INVALID_ENUM");
			break;
		case GL_INVALID_VALUE:
			Logger::Log("GL_INVALID_VALUE");
			break;
		case GL_INVALID_OPERATION:
			Logger::Log("GL_INVALID_OPERATION");
			break;
	#if not defined(PLATFORM_ANDROID)
		case GL_STACK_UNDERFLOW:
			Logger::Log("GL_STACK_UNDERFLOW");
			break;
		case GL_STACK_OVERFLOW:
			Logger::Log("GL_STACK_OVERFLOW");
			break;
	#endif
		case GL_OUT_OF_MEMORY:
			Logger::Log("GL_OUT_OF_MEMORY");
			break;
		default:
			std::stringstream ss;
			ss << "Something Else(" << error << ")";
			std::string s = ss.str();
			Logger::Log(s);
		}

		std::cout << std::endl;
		return true;
	}

	return false;
}
}
