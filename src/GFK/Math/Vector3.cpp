#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Vector2.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <cmath>

namespace gfk
{
	
Vector3::Vector3() :
X(0.0f), Y(0.0f), Z(0.0f)
{

}

Vector3::Vector3(const Vector2 v, float z) :
X(v.X), Y(v.Y), Z(z)
{

}

Vector3::Vector3(float x, float y, float z) :
X(x), Y(y), Z(z)
{

}
Vector3::Vector3(float value) :
X(value), Y(value), Z(value)
{

}

Vector3::~Vector3()
{

}

const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::Down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Left(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Forward(0.0f, 0.0f, -1.0f);
const Vector3 Vector3::Backward(0.0f, 0.0f, 1.0f);

void Vector3::Add(const Vector3 &v1, const Vector3 &v2, Vector3 &result)
{
	result.X = v1.X + v2.X;
	result.Y = v1.Y + v2.Y;
	result.Z = v1.Z + v2.Z;
}

Vector3 Vector3::Barycentric(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float amount1, float amount2)
{
	return Vector3(
		MathHelper::Barycentric(v1.X, v2.X, v3.X, amount1, amount2),
		MathHelper::Barycentric(v1.Y, v2.Y, v3.Y, amount1, amount2),
		MathHelper::Barycentric(v1.Z, v2.Z, v3.Z, amount1, amount2));

}

void Vector3::Barycentric(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, float amount1, float amount2, Vector3 &result)
{
	result.X = MathHelper::Barycentric(v1.X, v2.X, v3.X, amount1, amount2);
	result.Y = MathHelper::Barycentric(v1.Y, v2.Y, v3.Y, amount1, amount2);
	result.Z = MathHelper::Barycentric(v1.Z, v2.Z, v3.Z, amount1, amount2);
}

Vector3 Vector3::CatmullRom(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Vector3 &v4, float amount)
{
	return Vector3(
		MathHelper::CatmullRom(v1.X, v2.X, v3.X, v4.X, amount),
		MathHelper::CatmullRom(v1.Y, v2.Y, v3.Y, v4.Y, amount),
		MathHelper::CatmullRom(v1.Z, v2.Z, v3.Z, v4.Z, amount));
}

void Vector3::CatmullRom(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Vector3 &v4, float amount, Vector3 &result)
{
	result.X = MathHelper::CatmullRom(v1.X, v2.X, v3.X, v4.X, amount);
	result.Y = MathHelper::CatmullRom(v1.Y, v2.Y, v3.Y, v4.Y, amount);
	result.Z = MathHelper::CatmullRom(v1.Z, v2.Z, v3.Z, v4.Z, amount);
}

Vector3 Vector3::Clamp(const Vector3 &v, const Vector3 &min, const Vector3 &max)
{
	return Vector3(
		MathHelper::Clamp(v.X, min.X, max.X),
		MathHelper::Clamp(v.Y, min.Y, max.Y),
		MathHelper::Clamp(v.Z, min.Z, max.Z));
}

void Vector3::Clamp(const Vector3 &v, const Vector3 &min, const Vector3 &max, Vector3 &result)
{
	result.X = MathHelper::Clamp(v.X, min.X, max.X);
	result.Y = MathHelper::Clamp(v.Y, min.Y, max.Y);
	result.Z = MathHelper::Clamp(v.Z, min.Z, max.Z);
}

Vector3 Vector3::Cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(
		v1.Y * v2.Z - v2.Y * v1.Z,
		-(v1.X * v2.Z - v2.X * v1.Z),
		v1.X * v2.Y - v2.X * v1.Y);
}

void Vector3::Cross(const Vector3 &v1, const Vector3 &v2, Vector3 &result)
{
	result.X = v1.Y * v2.Z - v2.Y * v1.Z;
	result.Y = -(v1.X * v2.Z - v2.X * v1.Z);
	result.Z = v1.X * v2.Y - v2.X * v1.Y;
}

float Vector3::Distance(const Vector3 &v1, const Vector3 &v2)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	float z = v1.Z - v2.Z;
	return sqrt(x * x + y * y + z * z);
}

void Vector3::Distance(const Vector3 &v1, const Vector3 &v2, float &result)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	float z = v1.Z - v2.Z;
	result = sqrt(x * x + y * y + z * z);
}

float Vector3::DistanceSquared(const Vector3 &v1, const Vector3 &v2)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	float z = v1.Z - v2.Z;
	return x * x + y * y + z * z;
}

void Vector3::DistanceSquared(const Vector3 &v1, const Vector3 &v2, float &result)
{
	float x = v1.X - v2.X;
	float y = v1.Y - v2.Y;
	float z = v1.Z - v2.Z;
	result =  x * x + y * y + z * z;
}

void Vector3::Divide(const Vector3 &v, float scalar, Vector3 &result)
{
	result.X = v.X / scalar;
	result.Y = v.Y / scalar;
	result.Z = v.Z / scalar;
}

float Vector3::Dot(const Vector3 &v1, const Vector3 &v2)
{
	return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
}

void Vector3::Dot(const Vector3 &v1, const Vector3 &v2, float &result)
{
	result = v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
}

Vector3 Vector3::Hermite(const Vector3 &v1, const Vector3 &tangent1, const Vector3 &v2, const Vector3 &tangent2, float amount)
{
	return Vector3(
		MathHelper::Hermite(v1.X, tangent1.X, v2.X, tangent2.X, amount),
		MathHelper::Hermite(v1.Y, tangent1.Y, v2.Y, tangent2.Y, amount),
		MathHelper::Hermite(v1.Z, tangent1.Z, v2.Z, tangent2.Z, amount));
}

void Vector3::Hermite(const Vector3 &v1, const Vector3 &tangent1, const Vector3 &v2, const Vector3 &tangent2, float amount, Vector3 &result)
{
	result.X = MathHelper::Hermite(v1.X, tangent1.X, v2.X, tangent2.X, amount);
	result.Y = MathHelper::Hermite(v1.Y, tangent1.Y, v2.Y, tangent2.Y, amount);
	result.Z = MathHelper::Hermite(v1.Z, tangent1.Z, v2.Z, tangent2.Z, amount);
}

Vector3 Vector3::Lerp(const Vector3 &v1, const Vector3 &v2, float amount)
{
	return Vector3(
		MathHelper::Lerp(v1.X, v2.X, amount),
		MathHelper::Lerp(v1.Y, v2.Y, amount),
		MathHelper::Lerp(v1.Z, v2.Z, amount));
}

void Vector3::Lerp(const Vector3 &v1, const Vector3 &v2, float amount, Vector3 &result)
{
	result.X = MathHelper::Lerp(v1.X, v2.X, amount);
	result.Y = MathHelper::Lerp(v1.Y, v2.Y, amount);
	result.Z = MathHelper::Lerp(v1.Z, v2.Z, amount);
}

Vector3 Vector3::Max(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(
		v1.X > v2.X ? v1.X : v2.X,
		v1.Y > v2.Y ? v1.Y : v2.Y,
		v1.Z > v2.Z ? v1.Z : v2.Z);
}

void Vector3::Max(const Vector3 &v1, const Vector3 &v2, Vector3 &result)
{
	result.X = v1.X > v2.X ? v1.X : v2.X;
	result.Y = v1.Y > v2.Y ? v1.Y : v2.Y;
	result.Z = v1.Z > v2.Z ? v1.Z : v2.Z;
}

Vector3 Vector3::Min(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(
		v1.X < v2.X ? v1.X : v2.X,
		v1.Y < v2.Y ? v1.Y : v2.Y,
		v1.Z < v2.Z ? v1.Z : v2.Z);
}

void Vector3::Min(const Vector3 &v1, const Vector3 &v2, Vector3 &result)
{
	result.X = v1.X < v2.X ? v1.X : v2.X;
	result.Y = v1.Y < v2.Y ? v1.Y : v2.Y;
	result.Z = v1.Z < v2.Z ? v1.Z : v2.Z;
}

void Vector3::Multiply(const Vector3 &v1, float scalar, Vector3 &result)
{
	result.X = v1.X * scalar;
	result.Y = v1.Y * scalar;
	result.Z = v1.Z * scalar;
}

Vector3 Vector3::Negate(Vector3 &v)
{
	v.X = -v.X;
	v.Y = -v.Y;
	v.Z = -v.Z;
	return v;
}

void Vector3::Negate(const Vector3 &v, Vector3 &result)
{
	result.X = -v.X;
	result.Y = -v.Y;
	result.Z = -v.Z;
}

Vector3 Vector3::Normalize(Vector3 &v)
{
	float val = 1.0f / sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
	v.X *= val;
	v.Y *= val;
	v.Z *= val;
	return v;
}

void Vector3::Normalize(const Vector3 &v, Vector3 &result)
{
	result.X = v.X;
	result.Y = v.Y;
	result.Z = v.Z;
	float val = 1.0f / sqrt(result.X * result.X + result.Y * result.Y + result.Z * result.Z);
	result.X *= val;
	result.Y *= val;
	result.Z *= val;
}

Vector3 Vector3::Reflect(const Vector3 &v, const Vector3 &normal)
{
	Vector3 result(0.0f, 0.0f, 0.0f);
	float val = 2.0f * ((v.X * normal.X) + (v.Y * normal.Y) + (v.Z * normal.Z));
	result.X = v.X - (normal.X * val);
	result.Y = v.Y - (normal.Y * val);
	result.Z = v.Z - (normal.Z * val);
	return result;
}

void Vector3::Reflect(const Vector3 &v, const Vector3 &normal, Vector3 &result)
{
	float val = 2.0f * ((v.X * normal.X) + (v.Y * normal.Y) + (v.Z * normal.Z));
	result.X = v.X - (normal.X * val);
	result.Y = v.Y - (normal.Y * val);
	result.Z = v.Z - (normal.Z * val);
}

Vector3 Vector3::SmoothStep(const Vector3 &v1, const Vector3 &v2, float amount)
{
	return Vector3(
		MathHelper::SmoothStep(v1.X, v2.X, amount),
		MathHelper::SmoothStep(v1.Y, v2.Y, amount),
		MathHelper::SmoothStep(v1.Z, v2.Z, amount));
}

void Vector3::SmoothStep(const Vector3 &v1, const Vector3 &v2, float amount, Vector3 &result)
{
	result.X = MathHelper::SmoothStep(v1.X, v2.X, amount);
	result.Y = MathHelper::SmoothStep(v1.Y, v2.Y, amount);
	result.Z = MathHelper::SmoothStep(v1.Z, v2.Z, amount);
}

void Subtract(const Vector3 &v1, const Vector3 &v2, Vector3 &result)
{
	result.X = v1.X - v2.X;
	result.Y = v1.Y - v2.Y;
	result.Z = v1.Z - v2.Z;
}

Vector3 Vector3::Transform(const Vector3 &position, const Matrix &matrix)
{
	return Vector3(
		(position.X * matrix(1,1)) + (position.Y * matrix(2,1)) + (position.Z * matrix(3,1)) + matrix(4,1),
		(position.X * matrix(1,2)) + (position.Y * matrix(2,2)) + (position.Z * matrix(3,2)) + matrix(4,2),
		(position.X * matrix(1,3)) + (position.Y * matrix(2,3)) + (position.Z * matrix(3,3)) + matrix(4,3));
}

void Vector3::Transform(const Vector3 &position, const Matrix &matrix, Vector3 &result)
{
	result.X = (position.X * matrix(1,1)) + (position.Y * matrix(2,1)) + (position.Z * matrix(3,1)) + matrix(4,1);
	result.Y = (position.X * matrix(1,2)) + (position.Y * matrix(2,2)) + (position.Z * matrix(3,2)) + matrix(4,2);
	result.Z = (position.X * matrix(1,3)) + (position.Y * matrix(2,3)) + (position.Z * matrix(3,3)) + matrix(4,3);
}

Vector3 Vector3::Transform(const Vector3 &position, const Quaternion &quaternion)
{
	float x = 2 * (quaternion.Y * position.Z - quaternion.Z * position.Y);
	float y = 2 * (quaternion.Z * position.X - quaternion.X * position.Z);
	float z = 2 * (quaternion.X * position.Y - quaternion.Y * position.X);

	return Vector3(
		position.X + x * quaternion.W + (quaternion.Y * z - quaternion.Z * y),
		position.Y + y * quaternion.W + (quaternion.Z * x - quaternion.X * z),
		position.Z + z * quaternion.W + (quaternion.X * y - quaternion.Y * x));
}

void Vector3::Transform(const Vector3 &position, const Quaternion &quaternion, Vector3 &result)
{
	float x = 2 * (quaternion.Y * position.Z - quaternion.Z * position.Y);
	float y = 2 * (quaternion.Z * position.X - quaternion.X * position.Z);
	float z = 2 * (quaternion.X * position.Y - quaternion.Y * position.X);

	result.X = position.X + x * quaternion.W + (quaternion.Y * z - quaternion.Z * y);
	result.Y = position.Y + y * quaternion.W + (quaternion.Z * x - quaternion.X * z);
	result.Z = position.Z + z * quaternion.W + (quaternion.X * y - quaternion.Y * x);
}

Vector3 Vector3::TransformNormal(const Vector3 &normal, const Matrix &matrix)
{
	return Vector3(
		(normal.X * matrix(1,1)) + (normal.Y * matrix(2,1)) + (normal.Z * matrix(3,1)),
		(normal.X * matrix(1,2)) + (normal.Y * matrix(2,2)) + (normal.Z * matrix(3,2)),
		(normal.X * matrix(1,3)) + (normal.Y * matrix(2,3)) + (normal.Z * matrix(3,3)));
}

void Vector3::TransformNormal(const Vector3 &normal, const Matrix &matrix, Vector3 &result)
{
	result.X = (normal.X * matrix(1,1)) + (normal.Y * matrix(2,1)) + (normal.Z * matrix(3,1));
	result.Y = (normal.X * matrix(1,2)) + (normal.Y * matrix(2,2)) + (normal.Z * matrix(3,2));
	result.Z = (normal.X * matrix(1,3)) + (normal.Y * matrix(2,3)) + (normal.Z * matrix(3,3));
}

float Vector3::Length()
{
	return sqrt(X * X + Y * Y + Z * Z);
}

float Vector3::LengthSquared()
{
	return X * X + Y * Y + Z * Z;
}

void Vector3::Normalize()
{
	float val = 1.0f / sqrt(X * X + Y * Y + Z * Z);
	X *= val;
	Y *= val;
	Z *= val;
}

Vector3 Vector3::operator+= (const Vector3 &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	return *this;
}

Vector3 Vector3::operator-= (const Vector3 &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	return *this;
}

Vector3 Vector3::operator*= (float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
	return *this;
}

Vector3 Vector3::operator/= (float scalar)
{
	X /= scalar;
	Y /= scalar;
	Z /= scalar;
	return *this;
}

Vector3 operator+ (const Vector3 &op1, const Vector3 &op2)
{
	return Vector3(op1.X + op2.X, op1.Y + op2.Y, op1.Z + op2.Z);
}

Vector3 operator- (const Vector3 &op1, const Vector3 &op2)
{
	return Vector3(op1.X - op2.X, op1.Y - op2.Y, op1.Z - op2.Z);
}

Vector3 operator* (const Vector3 &op1, float scalar)
{
	return Vector3(op1.X * scalar, op1.Y * scalar, op1.Z * scalar);
}

Vector3 operator* (float scalar, const Vector3 &op2)
{
	return Vector3(op2.X * scalar, op2.Y * scalar, op2.Z * scalar);
}

Vector3 operator/ (const Vector3 &op2, float divisor)
{
	return Vector3(op2.X / divisor, op2.Y / divisor, op2.Z / divisor);
}

Vector3 operator- (const Vector3 &op1)
{
	return Vector3(-op1.X, -op1.Y, -op1.Z);
}

}
