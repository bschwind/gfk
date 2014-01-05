#pragma once

#include <GLFW/glfw3.h>
#include <GFK/Math/Vector2.hpp>

namespace gfk
{

class Mouse
{
public:
	static void SetTargetWindow(GLFWwindow* window);
	static Vector2 GetPos();
protected:
private:
	// The window to get mouse events from
	static GLFWwindow* targetWindow;
};
}
