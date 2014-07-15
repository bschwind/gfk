#include <GFK/Input/Mouse.hpp>

namespace gfk
{

GLFWwindow* Mouse::targetWindow;

void Mouse::SetTargetWindow(GLFWwindow* window)
{
	targetWindow = window;
	glfwSetInputMode(targetWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Vector2 Mouse::GetPos()
{
	double x;
	double y;

	glfwGetCursorPos(targetWindow, &x, &y);

	return Vector2((float)x, (float)y);
}

void Mouse::SetPos(const Vector2 &pos)
{
	glfwSetCursorPos(targetWindow, pos.X, pos.Y);
}

}
