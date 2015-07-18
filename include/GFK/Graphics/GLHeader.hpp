#pragma once

#include <GFK/OSDetection.hpp>
#include <map>
#include <string>

#if defined(PLATFORM_ANDROID)
	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#else
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif

namespace gfk
{

static std::map<std::string, GLint> GLSL_ATTRIB_MAP = {
	{"position", 0},
	{"color", 1},
	{"texCoord", 2},
	{"normal", 3},
	{"tangent", 4}
};

bool GLErrorCheck();

}
