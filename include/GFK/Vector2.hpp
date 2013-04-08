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

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 UnitX;
	static const Vector2 UnitY;

	static float Dot(const Vector2 &v1, const Vector2 &v2);
	static float Length(const Vector2 &v);
	static void Rotate(Vector2 &v, float angle);
	static void Normalize(Vector2 &v);
	static Vector2 Barycentric(Vector2 &v1, Vector2 &v2, Vector2 &v3, float amount1, float amount2);
	static Vector2 CatmullRom(Vector2 &v1, Vector2 &v2, Vector2 &v3, Vector2 &v4, float amount);
	static Vector2 Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max);
	static float Distance(const Vector2 &v1, const Vector2 &v2);
	static float DistanceSquared(const Vector2 &v1, const Vector2 &v2);
	static Vector2 Hermite(Vector2 &v1, Vector2 &tangent1, Vector2 &v2, Vector2 &tangent2, float amount);
	static Vector2 Reflect(const Vector2 &v, const Vector2 &normal);
protected:
private:
};

}