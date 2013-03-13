#include <GFK/Graphics/Color.hpp>

namespace gfk
{

Color::Color()
{
	R = G = B = 0.0f;
	A = 1.0f;
}

Color::Color(const float r, const float g, const float b)
{
	R = r; G = g; B = b;
	A = 1.0f;
}

Color::Color(const float r, const float g, const float b, const float a)
{
	R = r; G = g; B = b; A = a;
}

Color::~Color()
{

}

}