#include <GFK/Vector2.hpp>

namespace gfk
{
	Vector2::Vector2() :
	X(0.0f), Y(0.0f)
	{

	}

	Vector2::Vector2(const float x, const float y) :
	X(x), Y(y)
	{

	}

	Vector2::~Vector2()
	{

	}

	float Vector2::Dot(const Vector2 &v1, const Vector2 &v2)
	{
		return v1.X * v2.X + v1.Y * v2.Y;
	}
}