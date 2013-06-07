#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <cmath>

namespace gfk
{
	
Quaternion::Quaternion() :
X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
{

}

Quaternion::Quaternion(float x, float y, float z, float w) :
X(x), Y(y), Z(z), W(w)
{

}

Quaternion::Quaternion(Vector3 vector, float w) :
X(vector.X), Y(vector.Y), Z(vector.Z), W(w)
{

}

Quaternion::~Quaternion()
{

}

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

Quaternion Quaternion::Concatenate(const Quaternion &q1, const Quaternion &q2)
{
	Quaternion q;
	Concatenate(q1, q2, q);
	return q;
}

void Quaternion::Concatenate(const Quaternion &q1, const Quaternion &q2, Quaternion &result)
{
	float x = q2.X;
	float y = q2.Y;
	float z = q2.Z;
	float w = q2.W;
	float num4 = q1.X;
	float num3 = q1.Y;
	float num2 = q1.Z;
	float num = q1.W;
	float num12 = (y * num2) - (z * num3);
	float num11 = (z * num4) - (x * num2);
	float num10 = (x * num3) - (y * num4);
	float num9 = ((x * num4) + (y * num3)) + (z * num2);
	result.X = ((x * num) + (num4 * w)) + num12;
	result.Y = ((y * num) + (num3 * w)) + num11;
	result.Z = ((z * num) + (num2 * w)) + num10;
	result.W = (w * num) - num9;
}

Quaternion Quaternion::Conjugate(const Quaternion &value)
{
	Quaternion q;
	q.X = -value.X;
	q.Y = -value.Y;
	q.Z = -value.Z;
	q.W = value.W;
	return q;
}

void Quaternion::Conjugate(const Quaternion &value, Quaternion &result)
{
	result.X = -value.X;
	result.Y = -value.Y;
	result.Z = -value.Z;
	result.W = value.W;
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3 &axis, float angle)
{
	Quaternion q;
	CreateFromAxisAngle(axis, angle, q);
	return q;
}

void Quaternion::CreateFromAxisAngle(const Vector3 &axis, float angle, Quaternion &result)
{
	float num2 = angle * 0.5f;
	float num = (float) sin((double) num2);
	float num3 = (float) cos((double) num2);
	result.X = axis.X * num;
	result.Y = axis.Y * num;
	result.Z = axis.Z * num;
	result.W = num3;
}

Quaternion Quaternion::CreateFromRotationMatrix(const Matrix &matrix)
{
	Quaternion q;
	CreateFromRotationMatrix(matrix, q);
	return q;
}

void Quaternion::CreateFromRotationMatrix(const Matrix &matrix, Quaternion &result)
{
	float num8 = (matrix(1,1) + matrix(2,2)) + matrix(3,3);
	if (num8 > 0.0f)
	{
		float num = (float) sqrt((double) (num8 + 1.0f));
		result.W = num * 0.5f;
		num = 0.5f / num;
		result.X = (matrix(2,3) - matrix(3,2)) * num;
		result.Y = (matrix(3,1) - matrix(1,3)) * num;
		result.Z = (matrix(1,2) - matrix(2,1)) * num;
	}
	else if ((matrix(1,1) >= matrix(2,2)) && (matrix(1,1) >= matrix(3,3)))
	{
		float num7 = (float) sqrt((double) (((1.0f + matrix(1,1)) - matrix(2,2)) - matrix(3,3)));
		float num4 = 0.5f / num7;
		result.X = 0.5f * num7;
		result.Y = (matrix(1,2) + matrix(2,1)) * num4;
		result.Z = (matrix(1,3) + matrix(3,1)) * num4;
		result.W = (matrix(2,3) - matrix(3,2)) * num4;
	}
	else if (matrix(2,2) > matrix(3,3))
	{
		float num6 = (float) sqrt((double) (((1.0f + matrix(2,2)) - matrix(1,1)) - matrix(3,3)));
		float num3 = 0.5f / num6;
		result.X = (matrix(2,1) + matrix(1,2)) * num3;
		result.Y = 0.5f * num6;
		result.Z = (matrix(3,2) + matrix(2,3)) * num3;
		result.W = (matrix(3,1) - matrix(1,3)) * num3;
	}
	else
	{
		float num5 = (float) sqrt((double) (((1.0f + matrix(3,3)) - matrix(1,1)) - matrix(2,2)));
		float num2 = 0.5f / num5;
		result.X = (matrix(3,1) + matrix(1,3)) * num2;
		result.Y = (matrix(3,2) + matrix(2,3)) * num2;
		result.Z = 0.5f * num5;
		result.W = (matrix(1,2) - matrix(2,1)) * num2;
	}
}

Quaternion Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	Quaternion q;
	CreateFromYawPitchRoll(yaw, pitch, roll, q);
	return q;
}

void Quaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Quaternion &result)
{
	float num9 = roll * 0.5f;
	float num6 = (float) sin((double) num9);
	float num5 = (float) cos((double) num9);
	float num8 = pitch * 0.5f;
	float num4 = (float) sin((double) num8);
	float num3 = (float) cos((double) num8);
	float num7 = yaw * 0.5f;
	float num2 = (float) sin((double) num7);
	float num = (float) cos((double) num7);
	result.X = ((num * num4) * num5) + ((num2 * num3) * num6);
	result.Y = ((num2 * num3) * num5) - ((num * num4) * num6);
	result.Z = ((num * num3) * num6) - ((num2 * num4) * num5);
	result.W = ((num * num3) * num5) + ((num2 * num4) * num6);
}

float Quaternion::Dot(const Quaternion &q1, const Quaternion &q2)
{
	return ((((q1.X * q2.X) + (q1.Y * q2.Y)) + (q1.Z * q2.Z)) + (q1.W * q2.W));
}

void Quaternion::Dot(const Quaternion &q1, const Quaternion &q2, float &result)
{
	result = ((((q1.X * q2.X) + (q1.Y * q2.Y)) + (q1.Z * q2.Z)) + (q1.W * q2.W));
}

Quaternion Quaternion::Inverse(const Quaternion &value)
{
	Quaternion q;
	Inverse(value, q);
	return q;
}
void Quaternion::Inverse(const Quaternion &value, Quaternion &result)
{
	float num2 = (((value.X * value.X) + (value.Y * value.Y)) + (value.Z * value.Z)) + (value.W * value.W);
	float num = 1.0f / num2;
	result.X = -value.X * num;
	result.Y = -value.Y * num;
	result.Z = -value.Z * num;
	result.W = value.W * num;
}

Quaternion Quaternion::Lerp(const Quaternion &q1, const Quaternion &q2, float amount)
{
	Quaternion q;
	Lerp(q1, q2, amount, q);
	return q;
}

void Quaternion::Lerp(const Quaternion &q1, const Quaternion &q2, float amount, Quaternion &result)
{
	float num = amount;
	float num2 = 1.0f - num;
	float num5 = (((q1.X * q2.X) + (q1.Y * q2.Y)) + (q1.Z * q2.Z)) + (q1.W * q2.W);

	if (num5 >= 0.0f)
	{
		result.X = (num2 * q1.X) + (num * q2.X);
		result.Y = (num2 * q1.Y) + (num * q2.Y);
		result.Z = (num2 * q1.Z) + (num * q2.Z);
		result.W = (num2 * q1.W) + (num * q2.W);
	}
	else
	{
		result.X = (num2 * q1.X) - (num * q2.X);
		result.Y = (num2 * q1.Y) - (num * q2.Y);
		result.Z = (num2 * q1.Z) - (num * q2.Z);
		result.W = (num2 * q1.W) - (num * q2.W);
	}

	float num4 = (((result.X * result.X) + (result.Y * result.Y)) + (result.Z * result.Z)) + (result.W * result.W);
	float num3 = 1.0f / ((float) sqrt((double) num4));
	result.X *= num3;
	result.Y *= num3;
	result.Z *= num3;
	result.W *= num3;
}

Quaternion Quaternion::Slerp(const Quaternion &q1, const Quaternion &q2, float amount)
{
	Quaternion q;
	Slerp(q1, q2, amount, q);
	return q;
}

void Quaternion::Slerp(const Quaternion &q1, const Quaternion &q2, float amount, Quaternion &result)
{
	float num2;
	float num3;
	float num = amount;
	float num4 = (((q1.X * q2.X) + (q1.Y * q2.Y)) + (q1.Z * q2.Z)) + (q1.W * q2.W);
	bool flag = false;

	if (num4 < 0.0f)
	{
		flag = true;
		num4 = -num4;
	}
	if (num4 > 0.999999f)
	{
		num3 = 1.0f - num;
		num2 = flag ? -num : num;
	}
	else
	{
		float num5 = (float) acos((double) num4);
		float num6 = (float) (1.0 / sin((double) num5));
		num3 = ((float) sin((double) ((1.0f - num) * num5))) * num6;
		num2 = flag ? (((float) -sin((double) (num * num5))) * num6) : (((float) sin((double) (num * num5))) * num6);
	}

	result.X = (num3 * q1.X) + (num2 * q2.X);
	result.Y = (num3 * q1.Y) + (num2 * q2.Y);
	result.Z = (num3 * q1.Z) + (num2 * q2.Z);
	result.W = (num3 * q1.W) + (num2 * q2.W);
}

Quaternion Quaternion::Negate(const Quaternion &value)
{
	Quaternion q;
	Negate(value, q);
	return q;
}

void Quaternion::Negate(const Quaternion &value, Quaternion &result)
{
	result.X = -value.X;
	result.Y = -value.Y;
	result.Z = -value.Z;
	result.W = -value.W;
}

Quaternion Quaternion::Normalize(const Quaternion &value)
{
	Quaternion q;
	Normalize(value, q);
	return q;
}

void Quaternion::Normalize(const Quaternion &value, Quaternion &result)
{
	float num2 = (((value.X * value.X) + (value.Y * value.Y)) + (value.Z * value.Z)) + (value.W * value.W);
	float num = 1.0f / ((float) sqrt((double) num2));
	result.X = value.X * num;
	result.Y = value.Y * num;
	result.Z = value.Z * num;
	result.W = value.W * num;
}


void Quaternion::Conjugate()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

float Quaternion::Length()
{
	float num = X * X + Y * Y + Z * Z + W * W;
	return (float) sqrt((double) num);
}

float Quaternion::LengthSquared()
{
	return X * X + Y * Y + Z * Z + W * W;
}

void Quaternion::Normalize()
{
	float num2 = (((X * X) + (Y * Y)) + (Z * Z)) + (W * W);
	float num = 1.0f / ((float) sqrt((double) num2));
	X *= num;
	Y *= num;
	Z *= num;
	W *= num;
}

Quaternion Quaternion::operator+= (const Quaternion &op2)
{
	X += op2.X;
	Y += op2.Y;
	Z += op2.Z;
	W += op2.W;
	return *this;
}

Quaternion Quaternion::operator-= (const Quaternion &op2)
{
	X -= op2.X;
	Y -= op2.Y;
	Z -= op2.Z;
	W -= op2.W;
	return *this;
}

Quaternion Quaternion::operator*= (float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
	W *= scalar;
	return *this;
}

Quaternion Quaternion::operator/= (float scalar)
{
	X /= scalar;
	Y /= scalar;
	Z /= scalar;
	W /= scalar;
	return *this;
}

Quaternion operator+ (const Quaternion &op1, const Quaternion &op2)
{
	return Quaternion(op1.X + op2.X, op1.Y + op2.Y, op1.Z + op2.Z, op1.W + op2.W);
}

Quaternion operator- (const Quaternion &op1, const Quaternion &op2)
{
	return Quaternion(op1.X - op2.X, op1.Y - op2.Y, op1.Z - op2.Z, op1.W - op2.W);	
}

Quaternion operator- (const Quaternion &op1)
{
	Quaternion quaternion;
	quaternion.X = -op1.X;
	quaternion.Y = -op1.Y;
	quaternion.Z = -op1.Z;
	quaternion.W = -op1.W;
	return quaternion;
}

Quaternion operator/ (const Quaternion &op1, const Quaternion &op2)
{
	Quaternion quaternion;
	float x = op1.X;
	float y = op1.Y;
	float z = op1.Z;
	float w = op1.W;
	float num14 = (((op2.X * op2.X) + (op2.Y * op2.Y)) + (op2.Z * op2.Z)) + (op2.W * op2.W);
	float num5 = 1.0f / num14;
	float num4 = -op2.X * num5;
	float num3 = -op2.Y * num5;
	float num2 = -op2.Z * num5;
	float num = op2.W * num5;
	float num13 = (y * num2) - (z * num3);
	float num12 = (z * num4) - (x * num2);
	float num11 = (x * num3) - (y * num4);
	float num10 = ((x * num4) + (y * num3)) + (z * num2);
	quaternion.X = ((x * num) + (num4 * w)) + num13;
	quaternion.Y = ((y * num) + (num3 * w)) + num12;
	quaternion.Z = ((z * num) + (num2 * w)) + num11;
	quaternion.W = (w * num) - num10;
	return quaternion;
}

Quaternion operator* (const Quaternion &op1, const Quaternion &op2)
{
	Quaternion quaternion;
	float x = op1.X;
	float y = op1.Y;
	float z = op1.Z;
	float w = op1.W;
	float num4 = op2.X;
	float num3 = op2.Y;
	float num2 = op2.Z;
	float num = op2.W;
	float num12 = (y * num2) - (z * num3);
	float num11 = (z * num4) - (x * num2);
	float num10 = (x * num3) - (y * num4);
	float num9 = ((x * num4) + (y * num3)) + (z * num2);
	quaternion.X = ((x * num) + (num4 * w)) + num12;
	quaternion.Y = ((y * num) + (num3 * w)) + num11;
	quaternion.Z = ((z * num) + (num2 * w)) + num10;
	quaternion.W = (w * num) - num9;
	return quaternion;
}

Quaternion operator* (const Quaternion &op1, float op2)
{
	Quaternion quaternion;
	quaternion.X = op1.X * op2;
	quaternion.Y = op1.Y * op2;
	quaternion.Z = op1.Z * op2;
	quaternion.W = op1.W * op2;
	return quaternion;
}

}