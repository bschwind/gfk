#include <GFK/Graphics/GraphicsDevice.hpp>
#include <GFK/Graphics/MonitorConfig.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/PackedColor.hpp>
#include <GFK/Graphics/Shader.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

namespace gfk
{

// Render scene
void display(GLuint &vao);

// Initialize the data to be rendered
void initialize(GLuint &vao);

GLuint vao;

// Render scene
void display(GLuint &vao) {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void initialize(GLuint &vao) {
	// Use a Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 4 triangles to be rendered
	GLfloat vertices_position[24] = {
		0.0, 0.0,
		0.5, 0.0,
		0.5, 0.5,

		0.0, 0.0,
		0.0, 0.5,
		-0.5, 0.5,

		0.0, 0.0,
		-0.5, 0.0,
		-0.5, -0.5,		

		0.0, 0.0,
		0.0, -0.5,
		0.5, -0.5,
	};

	// Create a Vector Buffer Object that will store the vertices on video memory
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// Allocate space and upload the data from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);

	Shader shader = Shader::CreateFromFile("vertShader.vs", "fragShader.fs");

	// Get the location of the attributes that enter into the vertex shader
	GLint position_attribute = glGetAttribLocation(shader.Natives.OpenGL.ShaderID, "position");

	// Specify how the data for position can be accessed
	glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable the attribute
	glEnableVertexAttribArray(position_attribute);
}

GraphicsDevice::GraphicsDevice() :
gameShouldClose(false)
{

}

GraphicsDevice::~GraphicsDevice()
{
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwDestroyWindow(*iter);
	}
	
	glfwTerminate();
}

void GraphicsDevice::Initialize()
{
	InitializeWindows();

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	std::cout << "Initialized GLEW" << std::endl;

	initialize(vao);

	//glfwSwapInterval(0); - 0 for no VSync, 1 for VSync
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

void GraphicsDevice::SetClearColor(const gfk::Color &color)
{
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwMakeContextCurrent(*iter);
		glClearColor(color.R, color.G, color.B, color.A);
	}
}

void GraphicsDevice::SetClearColor(const gfk::PackedColor &color)
{
	glClearColor(color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void GraphicsDevice::SetDepthClearValue(float depth)
{
	glClearDepth(depth);
}

void GraphicsDevice::Clear()
{
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwMakeContextCurrent(*iter);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		display(vao);
	}
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
	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		glfwSwapBuffers(*iter);
	}
}

void GraphicsDevice::UpdateWindowEvents()
{
	glfwPollEvents();

	for (auto iter = windows.begin(); iter != windows.end(); ++iter)
	{
		if (glfwGetKey((*iter), GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(*iter)) {
			gameShouldClose = true;
		}
	}
}

bool GraphicsDevice::WindowShouldClose()
{
	return gameShouldClose;
}

void GraphicsDevice::error_callback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

}
