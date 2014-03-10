#include <GFK/Graphics/GraphicsDevice.hpp>
#include <GFK/Graphics/MonitorConfig.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/PackedColor.hpp>
#include <GFK/Graphics/GLHeader.hpp>
#include <iostream>

namespace gfk
{

GraphicsDevice::GraphicsDevice() :
gameShouldClose(false)
{

}

GraphicsDevice::~GraphicsDevice()
{
#if not defined(PLATFORM_ANDROID)
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwDestroyWindow(*iter);
	}
	
	glfwTerminate();
#endif
}

void GraphicsDevice::Initialize()
{
#if not defined(PLATFORM_ANDROID)
	InitializeWindows();
	InitializeGLEW();
	glfwSwapInterval(0);// - 0 for no VSync, 1 for VSync
#endif
}

#if not defined(PLATFORM_ANDROID)
void GraphicsDevice::InitializeGLEW()
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	std::cout << "Initialized GLEW" << std::endl;
}

void GraphicsDevice::InitializeWindows()
{
	// Initialize GLFW
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	// Enable 4x MSAA
	glfwWindowHint(GLFW_SAMPLES, 4);
	// Use OpenGL 3.2 core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	int monitorCount;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	int currentMonitorIndex = 0;
	int desiredWindowCount = MonitorConfig::GetMonitorCount();

	if (desiredWindowCount == 0)
	{
		// The user didn't specify a particular window layout
		// Give them a default setup
		primaryWindow = glfwCreateWindow(1280, 720, "GFK Game", NULL, NULL);
		windows.push_back(primaryWindow);
	}

	for (auto iter = MonitorConfig::begin(); iter != MonitorConfig::end(); ++iter)
	{
		if (currentMonitorIndex >= monitorCount)
		{
			// The user has requested more monitors than what we have, finish the loop
			break;
		}

		// This check is just so we can grab a pointer to the primary window
		// We will use this pointer to share its GL context with the other windows
		if (currentMonitorIndex == 0)
		{
			primaryWindow = glfwCreateWindow(
				iter->Width,
				iter->Height,
				iter->WindowName.c_str(),
				iter->IsFullScreen ? glfwGetPrimaryMonitor() : NULL,
				NULL);
			windows.push_back(primaryWindow);
		}
		else
		{
			GLFWwindow* newWindow = glfwCreateWindow(
				iter->Width,
				iter->Height,
				iter->WindowName.c_str(),
				iter->IsFullScreen ? monitors[currentMonitorIndex] : NULL,
				primaryWindow);
			if (!newWindow)
			{
				break;
			}
			windows.push_back(newWindow);
		}

		currentMonitorIndex++;
	}

	if (!primaryWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Check secondary monitors
	// Update the monitor list in monitor config

	glfwMakeContextCurrent(primaryWindow);
}
#endif

void GraphicsDevice::SetClearColor(const gfk::Color &color)
{
#if defined(PLATFORM_ANDROID)
	glClearColor(color.R, color.G, color.B, color.A);
#else
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwMakeContextCurrent(*iter);
		glClearColor(color.R, color.G, color.B, color.A);
	}
#endif
}

void GraphicsDevice::SetClearColor(const gfk::PackedColor &color)
{
	glClearColor(color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void GraphicsDevice::SetDepthClearValue(float depth)
{
#if defined(PLATFORM_ANDROID)
	glClearDepthf(depth);
#else
	glClearDepth(depth);
#endif
}

void GraphicsDevice::Clear()
{
#if defined(PLATFORM_ANDROID)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#else
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwMakeContextCurrent(*iter);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
#endif

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsDevice::ClearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::ClearColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsDevice::ResizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GraphicsDevice::SwapBuffers()
{
#if not defined(PLATFORM_ANDROID)
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwSwapBuffers(*iter);
	}

	glfwPollEvents();
#endif
}

void GraphicsDevice::UpdateWindowEvents()
{
#if not defined(PLATFORM_ANDROID)
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		if (glfwWindowShouldClose(*iter)) {
			gameShouldClose = true;
		}
	}
#endif
}

bool GraphicsDevice::WindowShouldClose()
{
	return gameShouldClose;
}

#if not defined(PLATFORM_ANDROID)
GLFWwindow* GraphicsDevice::GetPrimaryWindow()
{
	return primaryWindow;
}

std::vector<GLFWwindow*> GraphicsDevice::GetWindows()
{
	return windows;
}
#endif

void GraphicsDevice::error_callback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

}
