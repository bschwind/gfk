#pragma once

#include <GFK/OSDetection.hpp>

#if defined(PLATFORM_ANDROID)
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#else
	#include <GL/glew.h>
	#include <GLFW/glfw3.h>
#endif
