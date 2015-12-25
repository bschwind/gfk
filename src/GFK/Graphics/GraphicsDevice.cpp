#include <GFK/Game.hpp>
#include <GFK/Graphics/GraphicsDevice.hpp>
#include <GFK/Graphics/MonitorConfig.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/PackedColor.hpp>
#include <GFK/System/Logger.hpp>
#include <iostream>

namespace gfk
{

GraphicsDevice::GraphicsDevice() :
state(Uninitialized),
gameShouldClose(false)
{

}

GraphicsDevice::~GraphicsDevice()
{
	Uninitialize();
}

void GraphicsDevice::Initialize(const gfk::Game &game)
{
	if (state == Initialized)
	{
		return;
	}

#if defined(PLATFORM_ANDROID)
	InitializeAndroid(game);
#endif
#if !defined(PLATFORM_MOBILE)
	InitializeWindow(game);
	InitializeGLEW();
	glfwSwapInterval(0);// - 0 for no VSync, 1 for VSync
#endif

	state = Initialized;
}

void GraphicsDevice::Uninitialize()
{
	if (state == Uninitialized)
	{
		return;
	}
#if defined(PLATFORM_ANDROID)
	UninitializeAndroid();
#endif
#if !defined(PLATFORM_MOBILE)
	glfwDestroyWindow(primaryWindow);
	glfwTerminate();
#endif
	state = Uninitialized;
}

#if !defined(PLATFORM_MOBILE)
void GraphicsDevice::InitializeGLEW()
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		Logger::LogError("Failed to initalize GLEW");
		glfwTerminate();
		exit(-1);
	}

	// glewInit() will cause an error which we can ignore.
	// Clear it out because it's annoying
	glGetError();
}

void GraphicsDevice::InitializeWindow(const gfk::Game &game)
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

	primaryWindow = glfwCreateWindow(game.GetWidth(), game.GetHeight(), game.GetTitle().c_str(), NULL, NULL);

	if (!primaryWindow)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(primaryWindow);
}
#endif

#if defined(PLATFORM_ANDROID)
	int GraphicsDevice::InitializeAndroid(const gfk::Game &game)
	{
		Logger::Log("Start up OpenGL");
		// initialize OpenGL ES and EGL

		// Here specify the attributes of the desired configuration.
		// Below, we select an EGLConfig with at least 8 bits per color
		// component compatible with on-screen windows
		const EGLint attribs[] =
		{
				EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
				EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
				EGL_BLUE_SIZE, 8,
				EGL_GREEN_SIZE, 8,
				EGL_RED_SIZE, 8,
				EGL_DEPTH_SIZE, 16,
				EGL_NONE
		};

		EGLint AttribList[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		EGLint width, height;
		EGLint dummy;
		EGLint format;
		EGLint numConfigs;
		EGLConfig config;
		EGLSurface surface;
		EGLContext context;

		EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		eglInitialize(display, 0, 0);

		// Here, the application chooses the configuration it desires. In this
		// sample, we have a very simplified selection process, where we pick
		// the first EGLConfig that matches our criteria
		eglChooseConfig(display, attribs, &config, 1, &numConfigs);

		// EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
		// guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
		// As soon as we picked a EGLConfig, we can safely reconfigure the
		// ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID.
		eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

		ANativeWindow_setBuffersGeometry(game.GetAndroidApp()->window, 0, 0, format);

		surface = eglCreateWindowSurface(display, config, game.GetAndroidApp()->window, NULL);
		context = eglCreateContext(display, config, NULL, AttribList);

		if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
			// LOGW("Unable to eglMakeCurrent");
			Logger::Log("Unable to eglMakeCurrent");
			return -1;
		}

		eglQuerySurface(display, surface, EGL_WIDTH, &width);
		eglQuerySurface(display, surface, EGL_HEIGHT, &height);

		androidSurface.display = display;
		androidSurface.context = context;
		androidSurface.surface = surface;

		return 0;
	}

	void GraphicsDevice::UninitializeAndroid()
	{
		Logger::Log("Tear down OpenGL");

		if (androidSurface.display != EGL_NO_DISPLAY) {
		    eglMakeCurrent(androidSurface.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		    if (androidSurface.context != EGL_NO_CONTEXT) {
		        eglDestroyContext(androidSurface.display, androidSurface.context);
		    }
		    if (androidSurface.surface != EGL_NO_SURFACE) {
		        eglDestroySurface(androidSurface.display, androidSurface.surface);
		    }
		    eglTerminate(androidSurface.display);
		}

		androidSurface.display = EGL_NO_DISPLAY;
		androidSurface.context = EGL_NO_CONTEXT;
		androidSurface.surface = EGL_NO_SURFACE;
	}
#endif

void GraphicsDevice::SetClearColor(const gfk::Color &color)
{
	glClearColor(color.R, color.G, color.B, color.A);
	GLErrorCheck();
}

void GraphicsDevice::SetClearColor(const gfk::PackedColor &color)
{
	glClearColor(color.GetR(), color.GetG(), color.GetB(), color.GetA());
	GLErrorCheck();
}

void GraphicsDevice::SetDepthClearValue(float depth)
{
#if defined(PLATFORM_ANDROID) // PLATFORM_MOBILE?
	glClearDepthf(depth);
#else
	glClearDepth(depth);
#endif
	GLErrorCheck();
}

void GraphicsDevice::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLErrorCheck();

	glEnable(GL_BLEND);
	GLErrorCheck();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLErrorCheck();
}

void GraphicsDevice::ClearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	GLErrorCheck();
}

void GraphicsDevice::ClearColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLErrorCheck();
}

void GraphicsDevice::ResizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	GLErrorCheck();
}

void GraphicsDevice::SwapBuffers()
{
#if defined(PLATFORM_ANDROID)
	eglSwapBuffers(androidSurface.display, androidSurface.surface);
#endif
#if !defined(PLATFORM_ANDROID)
	glfwSwapBuffers(primaryWindow);
#endif
}

void GraphicsDevice::UpdateWindowEvents()
{
#if !defined(PLATFORM_ANDROID)
	glfwPollEvents();
	if (glfwWindowShouldClose(primaryWindow)) {
		gameShouldClose = true;
	}
#endif
}

bool GraphicsDevice::WindowShouldClose()
{
	return gameShouldClose;
}

#if !defined(PLATFORM_MOBILE)
GLFWwindow* GraphicsDevice::GetPrimaryWindow()
{
	return primaryWindow;
}
#endif

void GraphicsDevice::error_callback(int error, const char* description)
{
	std::cerr << "Error number: " << error << " " << description << std::endl;
}

}
