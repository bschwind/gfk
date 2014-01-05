#include <GFK/Input/Mouse.hpp>

namespace gfk
{

GLFWwindow* Mouse::targetWindow;

void Mouse::SetTargetWindow(GLFWwindow* window)
{
	targetWindow = window;
}

Vector2 Mouse::GetPos()
{
	double x;
	double y;

	glfwGetCursorPos(targetWindow, &x, &y);

	return Vector2((float)x, (float)y);
}

}