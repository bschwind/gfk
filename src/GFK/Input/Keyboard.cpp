#include <GFK/Input/Keyboard.hpp>

namespace gfk
{

GLFWwindow* Keyboard::targetWindow;

void Keyboard::SetTargetWindow(GLFWwindow* window)
{
	targetWindow = window;
}

bool Keyboard::IsKeyDown(int key)
{
	return glfwGetKey(targetWindow, key) == GLFW_PRESS;
}

bool Keyboard::IsKeyUp(int key)
{
	return glfwGetKey(targetWindow, key) == GLFW_RELEASE;
}

}