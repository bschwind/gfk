#pragma once

#include <GFK/Input/Keys.hpp>

namespace gfk
{

class Keyboard
{
public:
	static void SetTargetWindow(GLFWwindow* window);
	static bool IsKeyDown(int key);
	static bool IsKeyUp(int key);
protected:
private:
	// The window to get key events from
	static GLFWwindow* targetWindow;
};
}
