#include <GFK/Math/Vector2.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <cmath>

namespace gfk
{

Vector2::Vector2() :
X(0.0f), Y(0.0f)
{

}

Vector2::Vector2(float x, float y) :
X(x), Y(y)
{

}

Vector2::Vector2(float value) :
X(value), Y(value)
{

}

Vector2::~Vector2()
{

}

const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);

void Vector2::Add(const Vector2 &v1, const Vector2 &v2, Vector2 &result)
{
	result.X = v1.X + v2.X;
	result.Y = v1.Y + v2.Y;
}

Vector2 Vector2::Barycentric(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, float amount1, float amount2)
{
	return Vector2(
		MathHelper::Barycentric(v1.X, v2.X, v3.X, amount1, amount2),
		MathHelper::Barycentric(v1.Y, v2.Y, v3.Y, amount1, amount2));

}

void Vector2::Barycentric(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, float amount1, float amount2, Vector2 &result)
{
	result.X = MathHelper::Barycentric(v1.X, v2.X, v3.X, amount1, amount2);
	result.Y = MathHelper::Barycentric(v1.Y, v2.Y, v3.Y, amount1, amount2);
}

Vector2 Vector2::CatmullRom(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, Vector2 &v4, float amount)
{
	return Vector2(
		MathHelper::CatmullRom(v1.X, v2.X, v3.X, v4.X, amount),
		MathHelper::CatmullRom(v1.Y, v2.Y, v3.Y, v4.Y, amount));
}

void Vector2::CatmullRom(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, Vector2 &v4, float amount, Vector2 &result)
{
	result.X = MathHelper::CatmullRom(v1.X, v2.X, v3.X, v4.X, amount);
	result.Y = MathHelper::CatmullRom(v1.Y, v2.Y, v3.Y, v4.Y, amount);
}

Vector2 Vector2::Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max)
{
	return Vector2(
		MathHelper::Clamp(v.X, min.X, max.X),
		MathHelper::Clamp(v.Y, min.Y, max.Y));
}

void Vector2::Clamp(const Vector2 &v, const Vector2 &min, const Vector2 &max, Vector2 &result)
{
	result.X = MathHelper::Clamp(v.X, min.X, max.X);
	result.Y = MathHelper::Clamp(v.Y, min.Y, max.Y);
}

float Vector2::Distance(const Vector2 &v1, const Vector2 &v2)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	return sqrt(x * x + y * y);
}

void Vector2::Distance(const Vector2 &v1, const Vector2 &v2, float &result)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	result = sqrt(x * x + y * y);
}

float Vector2::DistanceSquared(const Vector2 &v1, const Vector2 &v2)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	return x * x + y * y;
}

void Vector2::DistanceSquared(const Vector2 &v1, const Vector2 &v2, float &result)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	result =  x * x + y * y;
}

void Vector2::Divide(const Vector2 &v, float scalar, Vector2 &result)
{
	result.X = v.X / scalar;
	result.Y = v.Y / scalar;
}

float Vector2::Dot(const Vector2 &v1, const Vector2 &v2)
{
	return v1.X * v2.X + v1.Y * v2.Y;
}

void Vector2::Dot(const Vector2 &v1, const Vector2 &v2, float &result)
{
	result = v1.X * v2.X + v1.Y * v2.Y;
}

Vector2 Vector2::Hermite(const Vector2 &v1, const Vector2 &tangent1, const Vector2 &v2, const Vector2 &tangent2, float amount)
{
	return Vector2(
		MathHelper::Hermite(v1.X, tangent1.X, v2.X, tangent2.X, amount), 
		MathHelper::Hermite(v1.Y, tangent1.Y, v2.Y, tangent2.Y, amount));
}

void Vector2::Hermite(const Vector2 &v1, const Vector2 &tangent1, const Vector2 &v2, const Vector2 &tangent2, float amount, Vector2 &result)
{
	result.X = MathHelper::Hermite(v1.X, tangent1.X, v2.X, tangent2.X, amount);
	result.Y = MathHelper::Hermite(v1.Y, tangent1.Y, v2.Y, tangent2.Y, amount);
}

Vector2 Vector2::Lerp(const Vector2 &v1, const Vector2 &v2, float amount)
{
	return Vector2(
		MathHelper::Lerp(v1.X, v2.X, amount), 
		MathHelper::Lerp(v1.Y, v2.Y, amount));
}

void Vector2::Lerp(const Vector2 &v1, const Vector2 &v2, float amount, Vector2 &result)
{
	result.X = MathHelper::Lerp(v1.X, v2.X, amount);
	result.Y = MathHelper::Lerp(v1.Y, v2.Y, amount);
}

Vector2 Vector2::Max(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2(
		v1.X > v2.X ? v1.X : v2.X,
		v1.Y > v2.Y ? v1.Y : v2.Y);
}

void Vector2::Max(const Vector2 &v1, const Vector2 &v2, Vector2 &result)
{
	result.X = v1.X > v2.X ? v1.X : v2.X;
	result.Y = v1.Y > v2.Y ? v1.Y : v2.Y;
}

Vector2 Vector2::Min(const Vector2 &v1, const Vector2 &v2)
{
	return Vector2(
		v1.X < v2.X ? v1.X : v2.X,
		v1.Y < v2.Y ? v1.Y : v2.Y);
}

void Vector2::Min(const Vector2 &v1, const Vector2 &v2, Vector2 &result)
{
	result.X = v1.X < v2.X ? v1.X : v2.X;
	result.Y = v1.Y < v2.Y ? v1.Y : v2.Y;
}

void Vector2::Multiply(const Vector2 &v, float scalar, Vector2 &result)
{
	result.X = v.X * scalar;
	result.Y = v.Y * scalar;
}

Vector2 Vector2::Negate(Vector2 &v)
{
	v.X = -v.X;
	v.Y = -v.Y;
	return v;
}

void Vector2::Negate(const Vector2 &v, Vector2 &result)
{
	result.X = -v.X;
	result.Y = -v.Y;
}

Vector2 Vector2::Normalize(Vector2 &v)
{
	float val = 1.0f / sqrt(v.X * v.X + v.Y * v.Y);
	v.X *= val;
	v.Y *= val;
	return v;
}

void Vector2::Normalize(const Vector2 &v, Vector2 &result)
{
	result.X = v.X;
	result.Y = v.Y;
	float val = 1.0f / sqrt(result.X * result.X + result.Y * result.Y);
	result.X *= val;
	result.Y *= val;
}

Vector2 Vector2::Reflect(const Vector2 &v, const Vector2 &normal)
{
	Vector2 result(0.0f, 0.0f);
	float val = 2.0f * ((v.X * normal.X) + (v.Y * normal.Y));
	result.X = v.X - (normal.X * val);
	result.Y = v.Y - (normal.Y * val);
	return result;
}

void Vector2::Reflect(const Vector2 &v, const Vector2 &normal, Vector2 &result)
{
	float val = 2.0f * ((v.X * normal.X) + (v.Y * normal.Y));
	result.X = v.X - (normal.X * val);
	result.Y = v.Y - (normal.Y * val);
}

Vector2 Vector2::Rotate(const Vector2 &v, float angle)
{
	float cosVal = cos(angle);
	float sinVal = sin(angle);

	return Vector2(
		cosVal * v.X - sinVal * v.Y,
		sinVal * v.X + cosVal * v.Y);
}

void Vector2::Rotate(const Vector2 &v, float angle, Vector2 &result)
{
	float cosVal = cos(angle);
	float sinVal = sin(angle);

	result.X = cosVal * v.X - sinVal * v.Y;
	result.Y = sinVal * v.X + cosVal * v.Y;
}

Vector2 Vector2::SmoothStep(const Vector2 &v1, const Vector2 &v2, float amount)
{
	return Vector2(
		MathHelper::SmoothStep(v1.X, v2.X, amount),
		MathHelper::SmoothStep(v1.Y, v2.Y, amount));
}

void Vector2::SmoothStep(const Vector2 &v1, const Vector2 &v2, float amount, Vector2 &result)
{
	result.X = MathHelper::SmoothStep(v1.X, v2.X, amount);
	result.Y = MathHelper::SmoothStep(v1.Y, v2.Y, amount);
}

void Vector2::Subtract(const Vector2 &v1, const Vector2 &v2, Vector2 &result)
{
	result.X = v1.X - v2.X;
	result.Y = v1.Y - v2.Y;
}

Vector2 Vector2::Transform(const Vector2 &position, const Matrix &matrix)
{
	return Vector2(
		(position.X * matrix(1,1)) + (position.Y * matrix(2,1)) + matrix(4,1),
		(position.X * matrix(1,2)) + (position.Y * matrix(2,2)) + matrix(4,2));
}

void Vector2::Transform(const Vector2 &position, const Matrix &matrix, Vector2 &result)
{
	result.X = (position.X * matrix(1,1)) + (position.Y * matrix(2,1)) + matrix(4,1);
	result.Y = (position.X * matrix(1,2)) + (position.Y * matrix(2,2)) + matrix(4,2);
}

Vector2 Vector2::TransformNormal(const Vector2 &normal, const Matrix matrix)
{
	return Vector2(
		(normal.X * matrix(1,1)) + (normal.Y * matrix(2,1)),
		(normal.X * matrix(1,2)) + (normal.Y * matrix(2,2)));
}

void Vector2::TransformNormal(const Vector2 &normal, const Matrix matrix, Vector2 &result)
{
	result.X = (normal.X * matrix(1,1)) + (normal.Y * matrix(2,1));
	result.Y = (normal.X * matrix(1,2)) + (normal.Y * matrix(2,2));
}

float Vector2::Length()
{
	return sqrt(X * X + Y * Y);
}

float Vector2::LengthSquared()
{
	return X * X + Y * Y;
}

void Vector2::Normalize()
{
	float val = 1.0f / sqrt(X * X + Y * Y);
	X *= val;
	Y *= val;
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

Vector2 operator+ (const Vector2 &op1, const Vector2 &op2)
{
	return Vector2(op1.X + op2.X, op1.Y + op2.Y);
}

Vector2 operator- (const Vector2 &op1, const Vector2 &op2)
{
	return Vector2(op1.X - op2.X, op1.Y - op2.Y);
}

Vector2 operator* (const Vector2 &op1, float scalar)
{
	return Vector2(op1.X * scalar, op1.Y * scalar);
}

Vector2 operator* (float scalar, const Vector2 &op2)
{
	return Vector2(op2.X * scalar, op2.Y * scalar);
}

Vector2 operator/ (const Vector2 &op2, float divisor)
{
	return Vector2(op2.X / divisor, op2.Y / divisor);
}

}