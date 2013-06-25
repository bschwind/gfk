#pragma once

namespace gfk
{

class Vector2;
class Matrix;

class Vector3
{
public:
	float X, Y, Z;
	Vector3();
	Vector3(const Vector2 v, float z);
	Vector3(float x, float y, float z);
	Vector3(float value);
	~Vector3();

	static const Vector3 Zero;
	static const Vector3 One;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Forward;
	static const Vector3 Backward;

	static void Add(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static Vector3 Barycentric(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float amount1, float amount2);
	static void Barycentric(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float amount1, float amount2, Vector3 &result);
	static Vector3 CatmullRom(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Vector3 &v4, float amount);
	static void CatmullRom(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Vector3 &v4, float amount, Vector3 &result);
	static Vector3 Clamp(const Vector3 &v, const Vector3 &min, const Vector3 &max);
	static void Clamp(const Vector3 &v, const Vector3 &min, const Vector3 &max, Vector3 &result);
	static Vector3 Cross(const Vector3 &v1, const Vector3 &v2);
	static void Cross(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static float Distance(const Vector3 &v1, const Vector3 &v2);
	static void Distance(const Vector3 &v1, const Vector3 &v2, float &result);
	static float DistanceSquared(const Vector3 &v1, const Vector3 &v2);
	static void DistanceSquared(const Vector3 &v1, const Vector3 &v2, float &result);
	static void Divide(const Vector3 &v, float scalar, Vector3 &result);
	static float Dot(const Vector3 &v1, const Vector3 &v2);
	static void Dot(const Vector3 &v1, const Vector3 &v2, float &result);
	static Vector3 Hermite(const Vector3 &v1, const Vector3 &tangent1, const Vector3 &v2, const Vector3 &tangent2, float amount);
	static void Hermite(const Vector3 &v1, const Vector3 &tangent1, const Vector3 &v2, const Vector3 &tangent2, float amount, Vector3 &result);
	static Vector3 Lerp(const Vector3 &v1, const Vector3 &v2, float amount);
	static void Lerp(const Vector3 &v1, const Vector3 &v2, float amount, Vector3 &result);
	static Vector3 Max(const Vector3 &v1, const Vector3 &v2);
	static void Max(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static Vector3 Min(const Vector3 &v1, const Vector3 &v2);
	static void Min(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static void Multiply(const Vector3 &v1, float scalar, Vector3 &result);
	static Vector3 Negate(Vector3 &v1);
	static void Negate(const Vector3 &v1, Vector3 &result);
	static Vector3 Normalize(Vector3 &v);
	static void Normalize(const Vector3 &v, Vector3 &result);
	static Vector3 Reflect(const Vector3 &v, const Vector3 &normal);
	static void Reflect(const Vector3 &v, const Vector3 &normal, Vector3 &result);
	static Vector3 SmoothStep(const Vector3 &v1, const Vector3 &v2, float amount);
	static void SmoothStep(const Vector3 &v1, const Vector3 &v2, float amount, Vector3 &result);
	static void Subtract(const Vector3 &v1, const Vector3 &v2, Vector3 &result);
	static Vector3 Transform(const Vector3 &position, const Matrix &matrix);
	static void Transform(const Vector3 &position, const Matrix &matrix, Vector3 &result);

	float Length();
	float LengthSquared();
	void Normalize();

	Vector3 operator+= (const Vector3 &op2);
	Vector3 operator-= (const Vector3 &op2);
	Vector3 operator*= (float scalar);
	Vector3 operator/= (float divisor);
protected:
private:
};

Vector3 operator+ (const Vector3 &op1, const Vector3 &op2);
Vector3 operator- (const Vector3 &op1, const Vector3 &op2);
Vector3 operator* (const Vector3 &op1, float scalar);
Vector3 operator* (float scalar, const Vector3 &op2);
Vector3 operator/ (const Vector3 &op1, float divisor);

}