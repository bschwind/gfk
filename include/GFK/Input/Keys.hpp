#pragma once

#include <GLFW/glfw3.h>

namespace gfk
{

class Keys
{
public:
	static const int Unknown = GLFW_KEY_UNKNOWN;
	static const int Space = GLFW_KEY_SPACE;
	static const int Apostrophe = GLFW_KEY_APOSTROPHE;
	static const int Comma = GLFW_KEY_COMMA;
	static const int Minus = GLFW_KEY_MINUS;
	static const int Period = GLFW_KEY_PERIOD;
	static const int Slash = GLFW_KEY_SLASH;
	static const int D0 = GLFW_KEY_0;
	static const int D1 = GLFW_KEY_1;
	static const int D2 = GLFW_KEY_2;
	static const int D3 = GLFW_KEY_3;
	static const int D4 = GLFW_KEY_4;
	static const int D5 = GLFW_KEY_5;
	static const int D6 = GLFW_KEY_6;
	static const int D7 = GLFW_KEY_7;
	static const int D8 = GLFW_KEY_8;
	static const int D9 = GLFW_KEY_9;
	static const int Semicolon = GLFW_KEY_SEMICOLON;
	static const int Equal = GLFW_KEY_EQUAL;
	static const int A = GLFW_KEY_A;
	static const int B = GLFW_KEY_B;
	static const int C = GLFW_KEY_C;
	static const int D = GLFW_KEY_D;
	static const int E = GLFW_KEY_E;
	static const int F = GLFW_KEY_F;
	static const int G = GLFW_KEY_G;
	static const int H = GLFW_KEY_H;
	static const int I = GLFW_KEY_I;
	static const int J = GLFW_KEY_J;
	static const int K = GLFW_KEY_K;
	static const int L = GLFW_KEY_L;
	static const int M = GLFW_KEY_M;
	static const int N = GLFW_KEY_N;
	static const int O = GLFW_KEY_O;
	static const int P = GLFW_KEY_P;
	static const int Q = GLFW_KEY_Q;
	static const int R = GLFW_KEY_R;
	static const int S = GLFW_KEY_S;
	static const int T = GLFW_KEY_T;
	static const int U = GLFW_KEY_U;
	static const int V = GLFW_KEY_V;
	static const int W = GLFW_KEY_W;
	static const int X = GLFW_KEY_X;
	static const int Y = GLFW_KEY_Y;
	static const int Z = GLFW_KEY_Z;
	static const int LeftBracket = GLFW_KEY_LEFT_BRACKET;
	static const int Backslash = GLFW_KEY_BACKSLASH;
	static const int RightBracket = GLFW_KEY_RIGHT_BRACKET;
	static const int GraveAccent = GLFW_KEY_GRAVE_ACCENT;
	static const int World1 = GLFW_KEY_WORLD_1;
	static const int World2 = GLFW_KEY_WORLD_2;
	static const int Escape = GLFW_KEY_ESCAPE;
	static const int Enter = GLFW_KEY_ENTER;
	static const int Tab = GLFW_KEY_TAB;
	static const int Backspace = GLFW_KEY_BACKSPACE;
	static const int Insert = GLFW_KEY_INSERT;
	static const int Delete = GLFW_KEY_DELETE;
	static const int Right = GLFW_KEY_RIGHT;
	static const int Left = GLFW_KEY_LEFT;
	static const int Down = GLFW_KEY_DOWN;
	static const int Up = GLFW_KEY_UP;
	static const int PageUp = GLFW_KEY_PAGE_UP;
	static const int PageDown = GLFW_KEY_PAGE_DOWN;
	static const int Home = GLFW_KEY_HOME;
	static const int End = GLFW_KEY_END;
	static const int CapsLock = GLFW_KEY_CAPS_LOCK;
	static const int ScrollLock = GLFW_KEY_SCROLL_LOCK;
	static const int NumLock = GLFW_KEY_NUM_LOCK;
	static const int PrintScreen = GLFW_KEY_PRINT_SCREEN;
	static const int Pause = GLFW_KEY_PAUSE;
	static const int F1 = GLFW_KEY_F1;
	static const int F2 = GLFW_KEY_F2;
	static const int F3 = GLFW_KEY_F3;
	static const int F4 = GLFW_KEY_F4;
	static const int F5 = GLFW_KEY_F5;
	static const int F6 = GLFW_KEY_F6;
	static const int F7 = GLFW_KEY_F7;
	static const int F8 = GLFW_KEY_F8;
	static const int F9 = GLFW_KEY_F9;
	static const int F10 = GLFW_KEY_F10;
	static const int F11 = GLFW_KEY_F11;
	static const int F12 = GLFW_KEY_F12;
	static const int F13 = GLFW_KEY_F13;
	static const int F14 = GLFW_KEY_F14;
	static const int F15 = GLFW_KEY_F15;
	static const int F16 = GLFW_KEY_F16;
	static const int F17 = GLFW_KEY_F17;
	static const int F18 = GLFW_KEY_F18;
	static const int F19 = GLFW_KEY_F19;
	static const int F20 = GLFW_KEY_F20;
	static const int F21 = GLFW_KEY_F21;
	static const int F22 = GLFW_KEY_F22;
	static const int F23 = GLFW_KEY_F23;
	static const int F24 = GLFW_KEY_F24;
	static const int F25 = GLFW_KEY_F25;
	static const int NumPad0 = GLFW_KEY_KP_0;
	static const int NumPad1 = GLFW_KEY_KP_1;
	static const int NumPad2 = GLFW_KEY_KP_2;
	static const int NumPad3 = GLFW_KEY_KP_3;
	static const int NumPad4 = GLFW_KEY_KP_4;
	static const int NumPad5 = GLFW_KEY_KP_5;
	static const int NumPad6 = GLFW_KEY_KP_6;
	static const int NumPad7 = GLFW_KEY_KP_7;
	static const int NumPad8 = GLFW_KEY_KP_8;
	static const int NumPad9 = GLFW_KEY_KP_9;
	static const int NumPadDecimal = GLFW_KEY_KP_DECIMAL;
	static const int NumPadDivide = GLFW_KEY_KP_DIVIDE;
	static const int NumPadMultiply = GLFW_KEY_KP_MULTIPLY;
	static const int NumPadSubtract = GLFW_KEY_KP_SUBTRACT;
	static const int NumPadAdd = GLFW_KEY_KP_ADD;
	static const int NumPadEnter = GLFW_KEY_KP_ENTER;
	static const int NumPadEqual = GLFW_KEY_KP_EQUAL;
	static const int LeftShift = GLFW_KEY_LEFT_SHIFT;
	static const int LeftControl = GLFW_KEY_LEFT_CONTROL;
	static const int LeftAlt = GLFW_KEY_LEFT_ALT;
	static const int LeftSuper = GLFW_KEY_LEFT_SUPER;
	static const int RightShift = GLFW_KEY_RIGHT_SHIFT;
	static const int RightControl = GLFW_KEY_RIGHT_CONTROL;
	static const int RightAlt = GLFW_KEY_RIGHT_ALT;
	static const int RightSuper = GLFW_KEY_RIGHT_SUPER;
	static const int Menu = GLFW_KEY_MENU;
	static const int Last = GLFW_KEY_LAST;
};

}