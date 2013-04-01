#pragma once

namespace gfk
{

class Vector2
{
public:
	float X, Y;
	Vector2();
	Vector2(const float x, const float y);
	~Vector2();

	static float Dot(const Vector2 &v1, const Vector2 &v2);
protected:
private:
};

}