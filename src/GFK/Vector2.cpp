#include <GFK/Vector2.hpp>
#include <GFK/MathHelper.hpp>
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

	const Vector2 Vector2::Zero(0.0f, 0.0f);
	const Vector2 Vector2::One(1.0f, 1.0f);
	const Vector2 Vector2::UnitX(1.0f, 0.0f);
	const Vector2 Vector2::UnitY(0.0f, 1.0f);

	Vector2 Vector2::Barycentric(Vector2 &v1, Vector2 &v2, Vector2 &v3, float amount1, float amount2)
	{
		return Vector2::Vector2(
			MathHelper::Barycentric(v1.X, v2.X, v3.X, amount1, amount2),
			MathHelper::Barycentric(v1.Y, v2.Y, v3.Y, amount1, amount2));

	}

	Vector2 Vector2::CatmullRom(Vector2 &v1, Vector2 &v2, Vector2 &v3, Vector2 &v4, float amount)
	{
		return Vector2::Vector2(
			MathHelper::CatmullRom(v1.X, v2.X, v3.X, v4.X, amount),
			MathHelper::CatmullRom(v1.Y, v2.Y, v3.Y, v4.Y, amount));
	}

	Vector2 Vector2::Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max)
	{
		return Vector2::Vector2(
			MathHelper::Clamp(v.X, min.X, max.X),
			MathHelper::Clamp(v.Y, min.Y, max.Y));
	}

	float Vector2::Distance(const Vector2 &v1, const Vector2 &v2)
	{
		float x = v1.X - v2.X;
		float y = v1.Y - v2.Y;
		return sqrt(x * x + y * y);
	}

	float Vector2::DistanceSquared(const Vector2 &v1, const Vector2 &v2)
	{
		float x = v1.X - v2.X;
		float y = v1.Y - v2.Y;
		return x * x + y * y;
	}

	float Vector2::Dot(const Vector2 &v1, const Vector2 &v2)
	{
		return v1.X * v2.X + v1.Y * v2.Y;
	}

	Vector2 Vector2::Hermite(Vector2 &v1, Vector2 &tangent1, Vector2 &v2, Vector2 &tangent2, float amount)
	{
		return Vector2::Vector2(
			MathHelper::Hermite(v1.X, tangent1.X, v2.X, tangent2.X, amount), 
			MathHelper::Hermite(v1.Y, tangent1.Y, v2.Y, tangent2.Y, amount));
	}

	float Vector2::Length(const Vector2 &v)
	{
		return sqrt(v.X * v.X + v.Y * v.Y);
	}

	float Vector2::LengthSquared(const Vector2 &v)
	{
		return v.X * v.X + v.Y * v.Y;
	}

	Vector2 Vector2::Lerp(const Vector2 &v1, const Vector2 &v2, float amount)
	{
		return Vector2::Vector2(
			MathHelper::Lerp(v1.X, v2.X, amount), 
			MathHelper::Lerp(v1.Y, v2.Y, amount));
	}

	Vector2 Vector2::Max(const Vector2 &v1, const Vector2 &v2)
	{
		return Vector2::Vector2(
			v1.X > v2.X ? v1.X : v2.X,
			v1.Y > v2.Y ? v1.Y : v2.Y);
	}

	Vector2 Vector2::Min(const Vector2 &v1, const Vector2 &v2)
	{
		return Vector2::Vector2(v1.X < v2.X ? v1.X : v2.X,
			v1.Y < v2.Y ? v1.Y : v2.Y);
	}

	Vector2 Vector2::Negate(Vector2 &v)
	{
		v.X = -v.X;
		v.Y = -v.Y;
		return v;
	}

	Vector2 Vector2::Negate(const Vector2 &v)
	{
		Vector2 vOut(v.X, v.Y);
		vOut.X = -vOut.X;
		vOut.Y = -vOut.Y;
		return vOut;
	}

	Vector2 Vector2::Normalize(Vector2 &v)
	{
		float length = sqrt(v.X * v.X + v.Y * v.Y);
		v.X /= length;
		v.Y /= length;
		return v;
	}

	Vector2 Vector2::Normalize(const Vector2 &v)
	{
		Vector2 vOut(v.X, v.Y);
		float length = sqrt(vOut.X * vOut.X + vOut.Y * vOut.Y);
		vOut.X /= length;
		vOut.Y /= length;
		return vOut;
	}

	Vector2 Vector2::Reflect(const Vector2 &v, const Vector2 &normal)
	{
		Vector2 result(0.0f, 0.0f);
		float val = 2.0f * ((v.X * normal.X) + (v.Y * normal.Y));
		result.X = v.X - (normal.X * val);
		result.Y = v.Y - (normal.Y * val);
		return result;
	}

	void Vector2::Rotate(Vector2 &v, float angle)
	{
		float cosVal = cos(angle);
		float sinVal = sin(angle);

		float temp = v.X;
		v.X = cosVal * v.X - sinVal * v.Y;
		v.Y = sinVal * temp + cosVal * v.Y;
	}

	Vector2 SmoothStep(Vector2 &v1, Vector2 &v2, float amount)
	{
		return Vector2::Vector2(
			MathHelper::SmoothStep(v1.X, v2.X, amount),
			MathHelper::SmoothStep(v1.Y, v2.Y, amount));
	}

	Vector2 operator+ (const Vector2 &op1, const Vector2 &op2)
	{
		return Vector2::Vector2(op1.X + op2.X, op1.Y + op2.Y);
	}

	Vector2 operator- (const Vector2 &op1, const Vector2 &op2)
	{
		return Vector2::Vector2(op1.X - op2.X, op1.Y - op2.Y);
	}

	Vector2 operator* (const Vector2 &op1, float scalar)
	{
		return Vector2::Vector2(op1.X * scalar, op1.Y * scalar);
	}

	Vector2 operator* (float scalar, const Vector2 &op2)
	{
		return Vector2::Vector2(op2.X * scalar, op2.Y * scalar);
	}

	Vector2 operator/ (const Vector2 &op2, float divisor)
	{
		return Vector2::Vector2(op2.X / divisor, op2.Y / divisor);
	}

	Vector2 Vector2::operator+= (const Vector2 &op2)
	{
		X += op2.X;
		Y += op2.Y;
		return *this;
	}

	Vector2 Vector2::operator-= (const Vector2 &op2)
	{
		X -= op2.X;
		Y -= op2.Y;
		return *this;
	}

	Vector2 Vector2::operator*= (float scalar)
	{
		X *= scalar;
		Y *= scalar;
		return *this;
	}

	Vector2 Vector2::operator/= (float scalar)
	{
		X /= scalar;
		Y /= scalar;
		return *this;
	}
}