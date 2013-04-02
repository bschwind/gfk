#include <GFK/Vector2.hpp>
#include <cmath>

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

	float Vector2::Length(const Vector2 &v)
	{
		return sqrt(v.X * v.X + v.Y * v.Y);
	}

	void Vector2::Rotate(Vector2 &v, float angle)
	{
		float cosVal = cos(angle);
		float sinVal = sin(angle);

		float temp = v.X;
		v.X = cosVal * v.X - sinVal * v.Y;
		v.Y = sinVal * temp + cosVal * v.Y;
	}

	void Vector2::Normalize(Vector2 &v)
	{
		float length = sqrt(v.X * v.X + v.Y * v.Y);
		v.X /= length;
		v.Y /= length;
	}
}