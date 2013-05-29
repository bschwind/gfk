#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Math/Vector3.hpp>
#include <stdexcept>
#include <cmath>

#define m11 matrix[0]
#define m12 matrix[4]
#define m13 matrix[8]
#define m14 matrix[12]
#define m21 matrix[1]
#define m22 matrix[5]
#define m23 matrix[9]
#define m24 matrix[13]
#define m31 matrix[2]
#define m32 matrix[6]
#define m33 matrix[10]
#define m34 matrix[14]
#define m41 matrix[3]
#define m42 matrix[7]
#define m43 matrix[11]
#define m44 matrix[15]

namespace gfk
{

Matrix::Matrix()
{

}

Matrix::Matrix(
	const float a11, const float a12, const float a13, const float a14,
	const float a21, const float a22, const float a23, const float a24,
	const float a31, const float a32, const float a33, const float a34,
	const float a41, const float a42, const float a43, const float a44) :
	matrix()
{
	m11 = a11;
	m12 = a12;
	m13 = a13;
	m14 = a14;
	m21 = a21;
	m22 = a22;
	m23 = a23;
	m24 = a24;
	m31 = a31;
	m32 = a32;
	m33 = a33;
	m34 = a34;
	m41 = a41;
	m42 = a42;
	m43 = a43;
	m44 = a44;
}

Matrix::~Matrix()
{

}

const Matrix Matrix::Identity(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);

Matrix Matrix::CreateBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &cameraUpVector, const Vector3 &cameraForwardVector)
{
	Matrix m;
	CreateBillboard(objectPosition, cameraPosition, cameraUpVector, cameraForwardVector, m);
	return m;
}

void Matrix::CreateBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &cameraUpVector, const Vector3 &cameraForwardVector, Matrix &result)
{
	Vector3 vector;
	Vector3 vector2;
	Vector3 vector3;
	vector = objectPosition - cameraPosition;
	float num = vector.LengthSquared();
	if (num < 0.0001f)
	{
		vector = cameraForwardVector;
	}
	else
	{
		vector *= (float)(1.0f / ((float)sqrt((double)num)));
	}
	Vector3::Cross(cameraUpVector, vector, vector3);
	vector3.Normalize();
	Vector3::Cross(vector, vector3, vector2);
	result.SetRight(vector3);
	result(1,4) = 0.0f;
	result.SetUp(vector2);
	result(2,4) = 0.0f;
	result.SetForward(vector);
	result(3,4) = 0.0f;
	result.SetTranslation(objectPosition);
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateConstrainedBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &rotateAxis, const Vector3 &cameraForwardVector, const Vector3 &objectForwardVector)
{
	Matrix m;
	CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, cameraForwardVector, objectForwardVector, m);
	return m;
}

void Matrix::CreateConstrainedBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &rotateAxis, const Vector3 &cameraForwardVector, const Vector3 &objectForwardVector, Matrix &result)
{
	float num;
	Vector3 vector;
	Vector3 vector2;
	Vector3 vector3;
	vector2.X = objectPosition.X - cameraPosition.X;
	vector2.Y = objectPosition.Y - cameraPosition.Y;
	vector2.Z = objectPosition.Z - cameraPosition.Z;
	float num2 = vector2.LengthSquared();
	if (num2 < 0.0001f)
	{
		vector2 = cameraForwardVector;
	}
	else
	{
		vector2 *= (float) (1.0f / ((float) sqrt((double) num2)));
	}
	Vector3 vector4 = rotateAxis;
	Vector3::Dot(rotateAxis, vector2, num);
	if (std::abs(num) > 0.9982547f)
	{
		vector = objectForwardVector;
		Vector3::Dot(rotateAxis, vector, num);
		if (std::abs(num) > 0.9982547f)
		{
			num = ((rotateAxis.X * Vector3::Forward.X) + (rotateAxis.Y * Vector3::Forward.Y)) + (rotateAxis.Z * Vector3::Forward.Z);
			vector = (std::abs(num) > 0.9982547f) ? Vector3::Right : Vector3::Forward;
		}
		Vector3::Cross(rotateAxis, vector, vector3);
		vector3.Normalize();
		Vector3::Cross(vector3, rotateAxis, vector);
		vector.Normalize();
	}
	else
	{
		Vector3::Cross(rotateAxis, vector2, vector3);
		vector3.Normalize();
		Vector3::Cross(vector3, vector4, vector);
		vector.Normalize();
	}

	result.SetRight(vector3);
	result(1,4) = 0.0f;
	result.SetUp(vector4);
	result(2,4) = 0.0f;
	result.SetForward(vector);
	result(3,4) = 0.0f;
	result.SetTranslation(objectPosition);
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateFromAxisAngle(const Vector3 &axis, const float angle)
{
	Matrix m;
	CreateFromAxisAngle(axis, angle, m);
	return m;
}

void Matrix::CreateFromAxisAngle(const Vector3 &axis, const float angle, Matrix &result)
{
	float x = axis.X;
	float y = axis.Y;
	float z = axis.Z;
	float num2 = (float) sin((double) angle);
	float num = (float) cos((double) angle);
	float num11 = x * x;
	float num10 = y * y;
	float num9 = z * z;
	float num8 = x * y;
	float num7 = x * z;
	float num6 = y * z;
	result(1,1) = num11 + (num * (1.0f - num11));
	result(1,2) = (num8 - (num * num8)) + (num2 * z);
	result(1,3) = (num7 - (num * num7)) - (num2 * y);
	result(1,4) = 0.0f;
	result(2,1) = (num8 - (num * num8)) - (num2 * z);
	result(2,2) = num10 + (num * (1.0f - num10));
	result(2,3) = (num6 - (num * num6)) + (num2 * x);
	result(2,4) = 0.0f;
	result(3,1) = (num7 - (num * num7)) + (num2 * y);
	result(3,2) = (num6 - (num * num6)) - (num2 * x);
	result(3,3) = num9 + (num * (1.0f - num9));
	result(3,4) = 0.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0f;
}

// static Matrix Matrix::CreateFromYawPitchRoll(const float yaw, const float pitch, const float roll)
// {
// 	// Matrix matrix;
// 	// Quaternion quaternion;
// 	// Quaternion.CreateFromYawPitchRoll(yaw, pitch, roll, out quaternion);
// 	// CreateFromQuaternion(ref quaternion, out matrix);
// 	// return matrix;
// }

// static void Matrix::CreateFromYawPitchRoll(const float yaw, const float pitch, const float roll, Matrix result)
// {
// 	// Matrix matrix;
// 	// Quaternion quaternion;
// 	// Quaternion.CreateFromYawPitchRoll(yaw, pitch, roll, out quaternion);
// 	// CreateFromQuaternion(ref quaternion, out matrix);
// 	// return matrix;
// }

Matrix Matrix::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector)
{
	Matrix m;
	CreateLookAt(cameraPosition, cameraTarget, cameraUpVector, m);
	return m;
}

void Matrix::CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector, Matrix &result)
{
	Vector3 cameraVec = cameraPosition - cameraTarget;
	Vector3 vector = Vector3::Normalize(cameraVec);
	Vector3 cross = Vector3::Cross(cameraUpVector, vector);
	Vector3 vector2 = Vector3::Normalize(cross);
	Vector3 vector3 = Vector3::Cross(vector, vector2);
	result(1,1) = vector2.X;
	result(1,2) = vector3.X;
	result(1,3) = vector.X;
	result(1,4) = 0.0f;
	result(2,1) = vector2.Y;
	result(2,2) = vector3.Y;
	result(2,3) = vector.Y;
	result(2,4) = 0.0f;
	result(3,1) = vector2.Z;
	result(3,2) = vector3.Z;
	result(3,3) = vector.Z;
	result(3,4) = 0.0f;
	result(4,1) = -Vector3::Dot(vector2, cameraPosition);
	result(4,2) = -Vector3::Dot(vector3, cameraPosition);
	result(4,3) = -Vector3::Dot(vector, cameraPosition);
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane)
{
	Matrix m;
	CreateOrthographic(width, height, zNearPlane, zFarPlane, m);
	return m;
}

void Matrix::CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane, Matrix &result)
{
	result(1,1) = 2.0f / width;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,2) = 2.0f / height;
	result(2,1) = 0.0f;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,3) = 1.0f / (zNearPlane - zFarPlane);
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,4) = 0.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = zNearPlane / (zNearPlane - zFarPlane);
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateOrthographicOffCenter(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane)
{
	Matrix m;
	CreateOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane, m);
	return m;
}

void Matrix::CreateOrthographicOffCenter(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane, Matrix &result)
{
	result(1,1) = (float)(2.0 / ((double)right - (double)left));
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,1) = 0.0f;
	result(2,2) = (float)(2.0 / ((double)top - (double)bottom));
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = (float)(1.0 / ((double)zNearPlane - (double)zFarPlane));
	result(3,4) = 0.0f;
	result(4,1) = (float)(((double)left + (double)right) / ((double)left - (double)right));
	result(4,2) = (float)(((double)top + (double)bottom) / ((double)bottom - (double)top));
	result(4,3) = (float)((double)zNearPlane / ((double)zNearPlane - (double)zFarPlane));
	result(4,4) = 1.0f;
}

Matrix Matrix::CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance)
{
	Matrix m;
	CreatePerspective(width, height, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance, Matrix &result)
{
	if (nearPlaneDistance <= 0.0f)
	{
		throw std::invalid_argument("nearPlaneDistance <= 0");
	}
	if (farPlaneDistance <= 0.0f)
	{
		throw std::invalid_argument("farPlaneDistance <= 0");
	}
	if (nearPlaneDistance >= farPlaneDistance)
	{
		throw std::invalid_argument("nearPlaneDistance >= farPlaneDistance");
	}
	result(1,1) = (2.0f * nearPlaneDistance) / width;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,2) = (2.0f * nearPlaneDistance) / height;
	result(2,1) = 0.0f;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,3) = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,4) = -1.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,4) = 0.0f;
	result(4,3) = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
}

Matrix Matrix::CreatePerspectiveFieldOfView(const float fieldOfView, const float aspectRatio, const float nearPlaneDistance, const float farPlaneDistance)
{
	Matrix m;
	CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreatePerspectiveFieldOfView(const float fieldOfView, const float aspectRatio, const float nearPlaneDistance, const float farPlaneDistance, Matrix &result)
{
	if ((fieldOfView <= 0.0f) || (fieldOfView >= 3.141593f))
	{
		throw std::invalid_argument("fieldOfView <= 0 or >= PI");
	}
	if (nearPlaneDistance <= 0.0f)
	{
		throw std::invalid_argument("nearPlaneDistance <= 0");
	}
	if (farPlaneDistance <= 0.0f)
	{
		throw std::invalid_argument("farPlaneDistance <= 0");
	}
	if (nearPlaneDistance >= farPlaneDistance)
	{
		throw std::invalid_argument("nearPlaneDistance >= farPlaneDistance");
	}
	float num = 1.0f / ((float) tan((double) (fieldOfView * 0.5f)));
	float num9 = num / aspectRatio;
	result(1,1) = num9;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0;
	result(2,2) = num;
	result(2,1) = 0.0f;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	result(3,4) = -1.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,4) = 0.0f;
	result(4,3) = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
}

Matrix Matrix::CreatePerspectiveOffCenter(const float left, const float right, const float bottom, const float top, const float nearPlaneDistance, const float farPlaneDistance)
{
	Matrix m;
	CreatePerspectiveOffCenter(left, right, bottom, top, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreatePerspectiveOffCenter(const float left, const float right, const float bottom, const float top, const float nearPlaneDistance, const float farPlaneDistance, Matrix &result)
{
	if (nearPlaneDistance <= 0.0f)
	{
		throw std::invalid_argument("nearPlaneDistance <= 0");
	}
	if (farPlaneDistance <= 0.0f)
	{
		throw std::invalid_argument("farPlaneDistance <= 0");
	}
	if (nearPlaneDistance >= farPlaneDistance)
	{
		throw std::invalid_argument("nearPlaneDistance >= farPlaneDistance");
	}

	result(1,1) = (2.0f * nearPlaneDistance) / (right - left);
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,2) = (2.0f * nearPlaneDistance) / (top - bottom);
	result(2,1) = 0.0f;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = (left + right) / (right - left);
	result(3,2) = (top + bottom) / (top - bottom);
	result(3,3) = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
	result(3,4) = -1.0f;
	result(4,3) = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,4) = 0.0f;
}

Matrix Matrix::CreateRotationX(const float radians)
{
	Matrix m;
	CreateRotationX(radians, m);
	return m;
}

void Matrix::CreateRotationX(const float radians, Matrix &result)
{
	result = Matrix::Identity;

	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	result(2,2) = val1;
	result(2,3) = val2;
	result(3,2) = -val2;
	result(3,3) = val1;
}

Matrix Matrix::CreateRotationY(const float radians)
{
	Matrix m;
	CreateRotationY(radians, m);
	return m;
}

void Matrix::CreateRotationY(const float radians, Matrix &result)
{
	result = Matrix::Identity;

	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	result(1,1) = val1;
	result(1,3) = -val2;
	result(3,1) = val2;
	result(3,3) = val1;
}

Matrix Matrix::CreateRotationZ(const float radians)
{
	Matrix m;
	CreateRotationZ(radians, m);
	return m;
}

void Matrix::CreateRotationZ(const float radians, Matrix &result)
{
	result = Matrix::Identity;

	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	result(1,1) = val1;
	result(1,2) = val2;
	result(2,1) = -val2;
	result(2,2) = val1;
}

Matrix Matrix::CreateScale(float scale)
{
	Matrix m;
	CreateScale(scale, m);
	return m;
}

void Matrix::CreateScale(float scale, Matrix &result)
{
	result(1,1) = scale;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,1) = 0.0f;
	result(2,2) = scale;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = scale;
	result(3,4) = 0.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateScale(float xScale, float yScale, float zScale)
{
	Matrix m;
	CreateScale(xScale, yScale, zScale, m);
	return m;
}

void Matrix::CreateScale(float xScale, float yScale, float zScale, Matrix &result)
{
	result(1,1) = xScale;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,1) = 0.0f;
	result(2,2) = yScale;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = zScale;
	result(3,4) = 0.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateScale(Vector3 scales)
{
	Matrix m;
	CreateScale(scales, m);
	return m;
}

void Matrix::CreateScale(Vector3 scales, Matrix &result)
{
	result(1,1) = scales.X;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,1) = 0.0f;
	result(2,2) = scales.Y;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = scales.Z;
	result(3,4) = 0.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0;
}

Matrix Matrix::CreateTranslation(const float xPosition, const float yPosition, const float zPosition)
{
	Matrix m;
	CreateTranslation(xPosition, yPosition, zPosition, m);
	return m;
}

void Matrix::CreateTranslation(const float xPosition, const float yPosition, const float zPosition, Matrix &result)
{
	result(1,1) = 1.0f;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,1) = 0.0f;
	result(2,2) = 1.0f;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = 1.0f;
	result(3,4) = 0.0f;
	result(4,1) = xPosition;
	result(4,2) = yPosition;
	result(4,3) = zPosition;
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateTranslation(const Vector3 position)
{
	Matrix m;
	CreateTranslation(position, m);
	return m;
}

void Matrix::CreateTranslation(const Vector3 position, Matrix &result)
{
	result(1,1) = 1.0f;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = 0.0f;
	result(2,1) = 0.0f;
	result(2,2) = 1.0f;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = 1.0f;
	result(3,4) = 0.0f;
	result(4,1) = position.X;
	result(4,2) = position.Y;
	result(4,3) = position.Z;
	result(4,4) = 1.0f;
}

// Matrix Matrix::CreateReflection(Plane value)
// {

// }

// void Matrix::CreateReflection(Plane value, Matrix &result)
// {

// }

Matrix Matrix::CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up)
{
	Matrix m;
	CreateWorld(position, forward, up, m);
	return m;
}

void Matrix::CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up, Matrix &result)
{
	Vector3 x, y, z;
	Vector3::Normalize(forward, z);
	Vector3::Cross(forward, up, x);
	Vector3::Cross(x, forward, y);
	x.Normalize();
	y.Normalize();            

	result = Matrix::Identity;
	result.SetRight(x);
	result.SetUp(y);
	result.SetForward(z);
	result.SetTranslation(position);
}

Matrix Matrix::Invert(const Matrix &matrix)
{
	Matrix m;
	Invert(matrix, m);
	return m;
}

void Matrix::Invert(const Matrix &matrix, Matrix &result)
{
	float num1 = matrix(1,1);
	float num2 = matrix(1,2);
	float num3 = matrix(1,3);
	float num4 = matrix(1,4);
	float num5 = matrix(2,1);
	float num6 = matrix(2,2);
	float num7 = matrix(2,3);
	float num8 = matrix(2,4);
	float num9 = matrix(3,1);
	float num10 = matrix(3,2);
	float num11 = matrix(3,3);
	float num12 = matrix(3,4);
	float num13 = matrix(4,1);
	float num14 = matrix(4,2);
	float num15 = matrix(4,3);
	float num16 = matrix(4,4);
	float num17 = (float) ((double) num11 * (double) num16 - (double) num12 * (double) num15);
	float num18 = (float) ((double) num10 * (double) num16 - (double) num12 * (double) num14);
	float num19 = (float) ((double) num10 * (double) num15 - (double) num11 * (double) num14);
	float num20 = (float) ((double) num9 * (double) num16 - (double) num12 * (double) num13);
	float num21 = (float) ((double) num9 * (double) num15 - (double) num11 * (double) num13);
	float num22 = (float) ((double) num9 * (double) num14 - (double) num10 * (double) num13);
	float num23 = (float) ((double) num6 * (double) num17 - (double) num7 * (double) num18 + (double) num8 * (double) num19);
	float num24 = (float) -((double) num5 * (double) num17 - (double) num7 * (double) num20 + (double) num8 * (double) num21);
	float num25 = (float) ((double) num5 * (double) num18 - (double) num6 * (double) num20 + (double) num8 * (double) num22);
	float num26 = (float) -((double) num5 * (double) num19 - (double) num6 * (double) num21 + (double) num7 * (double) num22);
	float num27 = (float) (1.0 / ((double) num1 * (double) num23 + (double) num2 * (double) num24 + (double) num3 * (double) num25 + (double) num4 * (double) num26));

	result(1,1) = num23 * num27;
	result(2,1) = num24 * num27;
	result(3,1) = num25 * num27;
	result(4,1) = num26 * num27;
	result(1,2) = (float) -((double) num2 * (double) num17 - (double) num3 * (double) num18 + (double) num4 * (double) num19) * num27;
	result(2,2) = (float) ((double) num1 * (double) num17 - (double) num3 * (double) num20 + (double) num4 * (double) num21) * num27;
	result(3,2) = (float) -((double) num1 * (double) num18 - (double) num2 * (double) num20 + (double) num4 * (double) num22) * num27;
	result(4,2) = (float) ((double) num1 * (double) num19 - (double) num2 * (double) num21 + (double) num3 * (double) num22) * num27;
	float num28 = (float) ((double) num7 * (double) num16 - (double) num8 * (double) num15);
	float num29 = (float) ((double) num6 * (double) num16 - (double) num8 * (double) num14);
	float num30 = (float) ((double) num6 * (double) num15 - (double) num7 * (double) num14);
	float num31 = (float) ((double) num5 * (double) num16 - (double) num8 * (double) num13);
	float num32 = (float) ((double) num5 * (double) num15 - (double) num7 * (double) num13);
	float num33 = (float) ((double) num5 * (double) num14 - (double) num6 * (double) num13);
	result(1,3) = (float) ((double) num2 * (double) num28 - (double) num3 * (double) num29 + (double) num4 * (double) num30) * num27;
	result(2,3) = (float) -((double) num1 * (double) num28 - (double) num3 * (double) num31 + (double) num4 * (double) num32) * num27;
	result(3,3) = (float) ((double) num1 * (double) num29 - (double) num2 * (double) num31 + (double) num4 * (double) num33) * num27;
	result(4,3) = (float) -((double) num1 * (double) num30 - (double) num2 * (double) num32 + (double) num3 * (double) num33) * num27;
	float num34 = (float) ((double) num7 * (double) num12 - (double) num8 * (double) num11);
	float num35 = (float) ((double) num6 * (double) num12 - (double) num8 * (double) num10);
	float num36 = (float) ((double) num6 * (double) num11 - (double) num7 * (double) num10);
	float num37 = (float) ((double) num5 * (double) num12 - (double) num8 * (double) num9);
	float num38 = (float) ((double) num5 * (double) num11 - (double) num7 * (double) num9);
	float num39 = (float) ((double) num5 * (double) num10 - (double) num6 * (double) num9);
	result(1,4) = (float) -((double) num2 * (double) num34 - (double) num3 * (double) num35 + (double) num4 * (double) num36) * num27;
	result(2,4) = (float) ((double) num1 * (double) num34 - (double) num3 * (double) num37 + (double) num4 * (double) num38) * num27;
	result(3,4) = (float) -((double) num1 * (double) num35 - (double) num2 * (double) num37 + (double) num4 * (double) num39) * num27;
	result(4,4) = (float) ((double) num1 * (double) num36 - (double) num2 * (double) num38 + (double) num3 * (double) num39) * num27;
}

Matrix Matrix::Lerp(const Matrix &matrix1, const Matrix &matrix2, const float amount)
{
	Matrix m;
	Lerp(matrix1, matrix2, amount, m);
	return m;
}

void Matrix::Lerp(const Matrix &matrix1, const Matrix &matrix2, const float amount, Matrix &result)
{
	result(1,1) = matrix1(1,1) + ((matrix2(1,1) - matrix1(1,1)) * amount);
	result(1,2) = matrix1(1,2) + ((matrix2(1,2) - matrix1(1,2)) * amount);
	result(1,3) = matrix1(1,3) + ((matrix2(1,3) - matrix1(1,3)) * amount);
	result(1,4) = matrix1(1,4) + ((matrix2(1,4) - matrix1(1,4)) * amount);
	result(2,1) = matrix1(2,1) + ((matrix2(2,1) - matrix1(2,1)) * amount);
	result(2,2) = matrix1(2,2) + ((matrix2(2,2) - matrix1(2,2)) * amount);
	result(2,3) = matrix1(2,3) + ((matrix2(2,3) - matrix1(2,3)) * amount);
	result(2,4) = matrix1(2,4) + ((matrix2(2,4) - matrix1(2,4)) * amount);
	result(3,1) = matrix1(3,1) + ((matrix2(3,1) - matrix1(3,1)) * amount);
	result(3,2) = matrix1(3,2) + ((matrix2(3,2) - matrix1(3,2)) * amount);
	result(3,3) = matrix1(3,3) + ((matrix2(3,3) - matrix1(3,3)) * amount);
	result(3,4) = matrix1(3,4) + ((matrix2(3,4) - matrix1(3,4)) * amount);
	result(4,1) = matrix1(4,1) + ((matrix2(4,1) - matrix1(4,1)) * amount);
	result(4,2) = matrix1(4,2) + ((matrix2(4,2) - matrix1(4,2)) * amount);
	result(4,3) = matrix1(4,3) + ((matrix2(4,3) - matrix1(4,3)) * amount);
	result(4,4) = matrix1(4,4) + ((matrix2(4,4) - matrix1(4,4)) * amount);
}

Matrix Matrix::Negate(const Matrix &matrix)
{
	Matrix m;
	Negate(matrix, m);
	return m;
}

void Matrix::Negate(const Matrix &matrix, Matrix &result)
{
	result(1,1) = -matrix(1,1);
	result(1,2) = -matrix(1,2);
	result(1,3) = -matrix(1,3);
	result(1,4) = -matrix(1,4);
	result(2,1) = -matrix(2,1);
	result(2,2) = -matrix(2,2);
	result(2,3) = -matrix(2,3);
	result(2,4) = -matrix(2,4);
	result(3,1) = -matrix(3,1);
	result(3,2) = -matrix(3,2);
	result(3,3) = -matrix(3,3);
	result(3,4) = -matrix(3,4);
	result(4,1) = -matrix(4,1);
	result(4,2) = -matrix(4,2);
	result(4,3) = -matrix(4,3);
	result(4,4) = -matrix(4,4);
}

Matrix Matrix::Transpose(const Matrix &matrix)
{
	Matrix m;
	Transpose(matrix, m);
	return m;
}

void Matrix::Transpose(const Matrix &matrix, Matrix &result)
{
	Matrix ret;

	ret(1,1) = matrix(1,1);
	ret(1,2) = matrix(2,1);
	ret(1,3) = matrix(3,1);
	ret(1,4) = matrix(4,1);

	ret(2,1) = matrix(1,2);
	ret(2,2) = matrix(2,2);
	ret(2,3) = matrix(3,2);
	ret(2,4) = matrix(4,2);

	ret(3,1) = matrix(1,3);
	ret(3,2) = matrix(2,3);
	ret(3,3) = matrix(3,3);
	ret(3,4) = matrix(4,3);

	ret(4,1) = matrix(1,4);
	ret(4,2) = matrix(2,4);
	ret(4,3) = matrix(3,4);
	ret(4,4) = matrix(4,4);

	result = ret;
}

float Matrix::Determinant()
{
	float num22 = m11;
	float num21 = m12;
	float num20 = m13;
	float num19 = m14;
	float num12 = m21;
	float num11 = m22;
	float num10 = m23;
	float num9 = m24;
	float num8 = m31;
	float num7 = m32;
	float num6 = m33;
	float num5 = m34;
	float num4 = m41;
	float num3 = m42;
	float num2 = m43;
	float num = m44;
	float num18 = (num6 * num) - (num5 * num2);
	float num17 = (num7 * num) - (num5 * num3);
	float num16 = (num7 * num2) - (num6 * num3);
	float num15 = (num8 * num) - (num5 * num4);
	float num14 = (num8 * num2) - (num6 * num4);
	float num13 = (num8 * num3) - (num7 * num4);

	return ((((num22 * (((num11 * num18) - (num10 * num17))
		+ (num9 * num16))) - (num21 * (((num12 * num18) - (num10 * num15))
		+ (num9 * num14)))) + (num20 * (((num12 * num17) - (num11 * num15))
		+ (num9 * num13)))) - (num19 * (((num12 * num16) - (num11 * num14)) + (num10 * num13))));
}

Vector3 Matrix::GetBackward()
{
	return Vector3(m31, m32, m33);
}

Vector3 Matrix::GetForward()
{
	return Vector3(-m31, -m32, -m33);
}

void Matrix::SetForward(const Vector3 &v)
{
	m31 = -v.X;
	m32 = -v.Y;
	m33 = -v.Z;
}

Vector3 Matrix::GetRight()
{
	return Vector3(m11, m12, m13);
}

void Matrix::SetRight(const Vector3 &v)
{
	m11 = v.X;
	m12 = v.Y;
	m13 = v.Z;
}

Vector3 Matrix::GetLeft()
{
	return Vector3(-m11, -m12, -m13);
}

Vector3 Matrix::GetUp()
{
	return Vector3(m21, m22, m23);
}

void Matrix::SetUp(const Vector3 &v)
{
	m21 = v.X;
	m22 = v.Y;
	m23 = v.Z;
}

Vector3 Matrix::GetDown()
{
	return Vector3(-m21, -m22, -m23);
}

Vector3 Matrix::GetTranslation()
{
	return Vector3(m41, m42, m43);
}

void Matrix::SetTranslation(const Vector3 &v)
{
	m41 = v.X;
	m42 = v.Y;
	m43 = v.Z;
}

}
