#pragma once

namespace gfk
{

class Vector2
{
public:
	float X, Y;
	Vector2();
	Vector2(float x, float y);
	Vector2(float value);
	~Vector2();

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 UnitX;
	static const Vector2 UnitY;

	static Vector2 Barycentric(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, float amount1, float amount2);
	static void Barycentric(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, float amount1, float amount2, Vector2 &result);
	static Vector2 CatmullRom(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, Vector2 &v4, float amount);
	static void CatmullRom(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, Vector2 &v4, float amount, Vector2 &result);
	static Vector2 Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max);
	static void Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max, Vector2 &result);
	static float Distance(const Vector2 &v1, const Vector2 &v2);
	static void Distance(const Vector2 &v1, const Vector2 &v2, float &result);
	static float DistanceSquared(const Vector2 &v1, const Vector2 &v2);
	static void DistanceSquared(const Vector2 &v1, const Vector2 &v2, float &result);
	static float Dot(const Vector2 &v1, const Vector2 &v2);
	static void Dot(const Vector2 &v1, const Vector2 &v2, float &result);
	static Vector2 Hermite(const Vector2 &v1, const Vector2 &tangent1, const Vector2 &v2, const Vector2 &tangent2, float amount);
	static void Hermite(const Vector2 &v1, const Vector2 &tangent1, const Vector2 &v2, const Vector2 &tangent2, float amount, Vector2 &result);
	static Vector2 Lerp(const Vector2 &v1, const Vector2 &v2, float amount);
	static void Lerp(const Vector2 &v1, const Vector2 &v2, float amount, Vector2 &result);
	static Vector2 Max(const Vector2 &v1, const Vector2 &v2);
	static void Max(const Vector2 &v1, const Vector2 &v2, Vector2 &result);
	static Vector2 Min(const Vector2 &v1, const Vector2 &v2);
	static void Min(const Vector2 &v1, const Vector2 &v2, Vector2 &result);
	static Vector2 Negate(Vector2 &v1);
	static void Negate(const Vector2 &v1, Vector2 &result);
	static Vector2 Normalize(Vector2 &v);
	static void Normalize(const Vector2 &v, Vector2 &result);
	static Vector2 Reflect(const Vector2 &v, const Vector2 &normal);
	static void Reflect(const Vector2 &v, const Vector2 &normal, Vector2 &result);
	static Vector2 Rotate(const Vector2 &v, float angle);
	static void Rotate(const Vector2 &v, float angle, Vector2 &result);
	static Vector2 SmoothStep(const Vector2 &v1, const Vector2 &v2, float amount);
	static void SmoothStep(const Vector2 &v1, const Vector2 &v2, float amount, Vector2 &result);
	//static void Transform();

	float Length();
	float LengthSquared();
	void Normalize();

	Vector2 operator+= (const Vector2 &op2);
	Vector2 operator-= (const Vector2 &op2);
	Vector2 operator*= (float scalar);
	Vector2 operator/= (float divisor);
protected:
private:
};

Vector2 operator+ (const Vector2 &op1, const Vector2 &op2);
Vector2 operator- (const Vector2 &op1, const Vector2 &op2);
Vector2 operator* (const Vector2 &op1, float scalar);
Vector2 operator* (float scalar, const Vector2 &op2);
Vector2 operator/ (const Vector2 &op1, float divisor);

}