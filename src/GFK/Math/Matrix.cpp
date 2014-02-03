#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/MathHelper.hpp>
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
	float a11, float a12, float a13, float a14,
	float a21, float a22, float a23, float a24,
	float a31, float a32, float a33, float a34,
	float a41, float a42, float a43, float a44)
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

void Add(const Matrix &m1, const Matrix &m2, Matrix &result)
{
	result(1,1) = m1(1,1) + m2(1,1);
	result(1,2) = m1(1,2) + m2(1,2);
	result(1,3) = m1(1,3) + m2(1,3);
	result(1,4) = m1(1,4) + m2(1,4);
	result(2,1) = m1(2,1) + m2(2,1);
	result(2,2) = m1(2,2) + m2(2,2);
	result(2,3) = m1(2,3) + m2(2,3);
	result(2,4) = m1(2,4) + m2(2,4);
	result(3,1) = m1(3,1) + m2(3,1);
	result(3,2) = m1(3,2) + m2(3,2);
	result(3,3) = m1(3,3) + m2(3,3);
	result(3,4) = m1(3,4) + m2(3,4);
	result(4,1) = m1(4,1) + m2(4,1);
	result(4,2) = m1(4,2) + m2(4,2);
	result(4,3) = m1(4,3) + m2(4,3);
	result(4,4) = m1(4,4) + m2(4,4);
}

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

Matrix Matrix::CreateFromAxisAngle(const Vector3 &axis, float angle)
{
	Matrix m;
	CreateFromAxisAngle(axis, angle, m);
	return m;
}

void Matrix::CreateFromAxisAngle(const Vector3 &axis, float angle, Matrix &result)
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

Matrix Matrix::CreateFromQuaternion(const Quaternion &quaternion)
{
	Matrix m;
	CreateFromQuaternion(quaternion, m);
	return m;
}

void Matrix::CreateFromQuaternion(const Quaternion &quaternion, Matrix &result)
{
	float num9 = quaternion.X * quaternion.X;
	float num8 = quaternion.Y * quaternion.Y;
	float num7 = quaternion.Z * quaternion.Z;
	float num6 = quaternion.X * quaternion.Y;
	float num5 = quaternion.Z * quaternion.W;
	float num4 = quaternion.Z * quaternion.X;
	float num3 = quaternion.Y * quaternion.W;
	float num2 = quaternion.Y * quaternion.Z;
	float num = quaternion.X * quaternion.W;
	result(1,1) = 1.0f - (2.0f * (num8 + num7));
	result(1,2) = 2.0f * (num6 + num5);
	result(1,3) = 2.0f * (num4 - num3);
	result(1,4) = 0.0f;
	result(2,1) = 2.0f * (num6 - num5);
	result(2,2) = 1.0f - (2.0f * (num7 + num9));
	result(2,3) = 2.0f * (num2 + num);
	result(2,4) = 0.0f;
	result(3,1) = 2.0f * (num4 + num3);
	result(3,2) = 2.0f * (num2 - num);
	result(3,3) = 1.0f - (2.0f * (num8 + num9));
	result(3,4) = 0.0f;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
{
	Matrix m;
	CreateFromYawPitchRoll(yaw, pitch, roll, m);
	return m;	
}

void Matrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix result)
{
	Quaternion quaternion;
	Quaternion::CreateFromYawPitchRoll(yaw, pitch, roll, quaternion);
	CreateFromQuaternion(quaternion, result);
}

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
	result(1,2) = vector2.Y;
	result(1,3) = vector2.Z;
	result(1,4) = -Vector3::Dot(vector2, cameraPosition);
	result(2,1) = vector3.X;
	result(2,2) = vector3.Y;
	result(2,3) = vector3.Z;
	result(2,4) = -Vector3::Dot(vector3, cameraPosition);
	result(3,1) = vector.X;
	result(3,2) = vector.Y;
	result(3,3) = vector.Z;
	result(3,4) = -Vector3::Dot(vector, cameraPosition);
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
{
	Matrix m;
	CreateOrthographic(width, height, zNearPlane, zFarPlane, m);
	return m;
}

void Matrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane, Matrix &result)
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

Matrix Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
{
	Matrix m;
	CreateOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane, m);
	return m;
}

void Matrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane, Matrix &result)
{
	result(1,1) = (float)(2.0 / ((double)right - (double)left));
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = -(float)(((double)right + (double)left) / ((double)right - (double)left));
	result(2,1) = 0.0f;
	result(2,2) = (float)(2.0 / ((double)top - (double)bottom));
	result(2,3) = 0.0f;
	result(2,4) = -(float)(((double)top + (double)bottom) / ((double)top - (double)bottom));
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = -(float)(2.0 / ((double)zFarPlane - (double)zNearPlane));
	result(3,4) = -(float)(((double)zFarPlane + (double)zNearPlane) / ((double)zFarPlane - (double)zNearPlane));
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateOrthographicUpperLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix m;
	CreateOrthographicOffCenter(0.0f, screenWidth, screenHeight, 0, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreateOrthographicUpperLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance, Matrix &result)
{
	CreateOrthographicOffCenter(0.0f, screenWidth, screenHeight, 0, nearPlaneDistance, farPlaneDistance, result);
}

Matrix Matrix::CreateOrthographicBottomLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix m;
	CreateOrthographicOffCenter(0.0f, screenWidth, 0, screenHeight, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreateOrthographicBottomLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance, Matrix &result)
{
	return CreateOrthographicOffCenter(0.0f, screenWidth, 0, screenHeight, nearPlaneDistance, farPlaneDistance, result);
}

Matrix Matrix::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix m;
	CreatePerspective(width, height, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance, Matrix &result)
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

Matrix Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix m;
	CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance, Matrix &result)
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
	result(2,1) = 0.0f;
	result(2,2) = num;
	result(2,3) = 0.0f;
	result(2,4) = 0.0f;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = (farPlaneDistance + nearPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
	result(3,4) = (2 * farPlaneDistance * nearPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = -1.0f;
	result(4,4) = 0.0f;
}

Matrix Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance)
{
	Matrix m;
	CreatePerspectiveOffCenter(left, right, bottom, top, nearPlaneDistance, farPlaneDistance, m);
	return m;
}

void Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance, Matrix &result)
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

Matrix Matrix::CreateRotationX(float radians)
{
	Matrix m;
	CreateRotationX(radians, m);
	return m;
}

void Matrix::CreateRotationX(float radians, Matrix &result)
{
	result = Matrix::Identity;

	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	result(2,2) = val1;
	result(2,3) = -val2;
	result(3,2) = val2;
	result(3,3) = val1;
}

Matrix Matrix::CreateRotationY(float radians)
{
	Matrix m;
	CreateRotationY(radians, m);
	return m;
}

void Matrix::CreateRotationY(float radians, Matrix &result)
{
	result = Matrix::Identity;

	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	result(1,1) = val1;
	result(1,3) = val2;
	result(3,1) = -val2;
	result(3,3) = val1;
}

Matrix Matrix::CreateRotationZ(float radians)
{
	Matrix m;
	CreateRotationZ(radians, m);
	return m;
}

void Matrix::CreateRotationZ(float radians, Matrix &result)
{
	result = Matrix::Identity;

	float val1 = (float)cos(radians);
	float val2 = (float)sin(radians);

	result(1,1) = val1;
	result(1,2) = -val2;
	result(2,1) = val2;
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

Matrix Matrix::CreateScale(const Vector3 &scales)
{
	Matrix m;
	CreateScale(scales, m);
	return m;
}

void Matrix::CreateScale(const Vector3 &scales, Matrix &result)
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

Matrix Matrix::CreateTranslation(float xPosition, float yPosition, float zPosition)
{
	Matrix m;
	CreateTranslation(xPosition, yPosition, zPosition, m);
	return m;
}

void Matrix::CreateTranslation(float xPosition, float yPosition, float zPosition, Matrix &result)
{
	result(1,1) = 1.0f;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = xPosition;
	result(2,1) = 0.0f;
	result(2,2) = 1.0f;
	result(2,3) = 0.0f;
	result(2,4) = yPosition;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = 1.0f;
	result(3,4) = zPosition;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
	result(4,4) = 1.0f;
}

Matrix Matrix::CreateTranslation(const Vector3 &position)
{
	Matrix m;
	CreateTranslation(position, m);
	return m;
}

void Matrix::CreateTranslation(const Vector3 &position, Matrix &result)
{
	result(1,1) = 1.0f;
	result(1,2) = 0.0f;
	result(1,3) = 0.0f;
	result(1,4) = position.X;
	result(2,1) = 0.0f;
	result(2,2) = 1.0f;
	result(2,3) = 0.0f;
	result(2,4) = position.Y;
	result(3,1) = 0.0f;
	result(3,2) = 0.0f;
	result(3,3) = 1.0f;
	result(3,4) = position.Z;
	result(4,1) = 0.0f;
	result(4,2) = 0.0f;
	result(4,3) = 0.0f;
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

void Matrix::Divide(const Matrix &m, float divisor, Matrix &result)
{
	float num = 1.0f / divisor;
	result(1,1) = m(1,1) * num;
	result(1,2) = m(1,2) * num;
	result(1,3) = m(1,3) * num;
	result(1,4) = m(1,4) * num;
	result(2,1) = m(2,1) * num;
	result(2,2) = m(2,2) * num;
	result(2,3) = m(2,3) * num;
	result(2,4) = m(2,4) * num;
	result(3,1) = m(3,1) * num;
	result(3,2) = m(3,2) * num;
	result(3,3) = m(3,3) * num;
	result(3,4) = m(3,4) * num;
	result(4,1) = m(4,1) * num;
	result(4,2) = m(4,2) * num;
	result(4,3) = m(4,3) * num;
	result(4,4) = m(4,4) * num;
}

void Matrix::Divide(const Matrix &m1, const Matrix &m2, Matrix &result)
{
	result(1,1) = m1(1,1) / m2(1,1);
	result(1,2) = m1(1,2) / m2(1,2);
	result(1,3) = m1(1,3) / m2(1,3);
	result(1,4) = m1(1,4) / m2(1,4);
	result(2,1) = m1(2,1) / m2(2,1);
	result(2,2) = m1(2,2) / m2(2,2);
	result(2,3) = m1(2,3) / m2(2,3);
	result(2,4) = m1(2,4) / m2(2,4);
	result(3,1) = m1(3,1) / m2(3,1);
	result(3,2) = m1(3,2) / m2(3,2);
	result(3,3) = m1(3,3) / m2(3,3);
	result(3,4) = m1(3,4) / m2(3,4);
	result(4,1) = m1(4,1) / m2(4,1);
	result(4,2) = m1(4,2) / m2(4,2);
	result(4,3) = m1(4,3) / m2(4,3);
	result(4,4) = m1(4,4) / m2(4,4);
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

Matrix Matrix::Lerp(const Matrix &m1, const Matrix &m2, float amount)
{
	Matrix m;
	Lerp(m1, m2, amount, m);
	return m;
}

void Matrix::Lerp(const Matrix &m1, const Matrix &m2, float amount, Matrix &result)
{
	result(1,1) = m1(1,1) + ((m2(1,1) - m1(1,1)) * amount);
	result(1,2) = m1(1,2) + ((m2(1,2) - m1(1,2)) * amount);
	result(1,3) = m1(1,3) + ((m2(1,3) - m1(1,3)) * amount);
	result(1,4) = m1(1,4) + ((m2(1,4) - m1(1,4)) * amount);
	result(2,1) = m1(2,1) + ((m2(2,1) - m1(2,1)) * amount);
	result(2,2) = m1(2,2) + ((m2(2,2) - m1(2,2)) * amount);
	result(2,3) = m1(2,3) + ((m2(2,3) - m1(2,3)) * amount);
	result(2,4) = m1(2,4) + ((m2(2,4) - m1(2,4)) * amount);
	result(3,1) = m1(3,1) + ((m2(3,1) - m1(3,1)) * amount);
	result(3,2) = m1(3,2) + ((m2(3,2) - m1(3,2)) * amount);
	result(3,3) = m1(3,3) + ((m2(3,3) - m1(3,3)) * amount);
	result(3,4) = m1(3,4) + ((m2(3,4) - m1(3,4)) * amount);
	result(4,1) = m1(4,1) + ((m2(4,1) - m1(4,1)) * amount);
	result(4,2) = m1(4,2) + ((m2(4,2) - m1(4,2)) * amount);
	result(4,3) = m1(4,3) + ((m2(4,3) - m1(4,3)) * amount);
	result(4,4) = m1(4,4) + ((m2(4,4) - m1(4,4)) * amount);
}

void Matrix::Multiply(const Matrix &m, float scalar, Matrix &result)
{
	result(1,1) = m(1,1) * scalar;
	result(1,2) = m(1,2) * scalar;
	result(1,3) = m(1,3) * scalar;
	result(1,4) = m(1,4) * scalar;
	result(2,1) = m(2,1) * scalar;
	result(2,2) = m(2,2) * scalar;
	result(2,3) = m(2,3) * scalar;
	result(2,4) = m(2,4) * scalar;
	result(3,1) = m(3,1) * scalar;
	result(3,2) = m(3,2) * scalar;
	result(3,3) = m(3,3) * scalar;
	result(3,4) = m(3,4) * scalar;
	result(4,1) = m(4,1) * scalar;
	result(4,2) = m(4,2) * scalar;
	result(4,3) = m(4,3) * scalar;
	result(4,4) = m(4,4) * scalar;
}

void Matrix::Multiply(const Matrix &m1, const Matrix &m2, Matrix &result)
{
	float num11 = (((m1(1,1) * m2(1,1)) + (m1(1,2) * m2(2,1))) + (m1(1,3) * m2(3,1))) + (m1(1,4) * m2(4,1));
	float num12 = (((m1(1,1) * m2(1,2)) + (m1(1,2) * m2(2,2))) + (m1(1,3) * m2(3,2))) + (m1(1,4) * m2(4,2));
	float num13 = (((m1(1,1) * m2(1,3)) + (m1(1,2) * m2(2,3))) + (m1(1,3) * m2(3,3))) + (m1(1,4) * m2(4,3));
	float num14 = (((m1(1,1) * m2(1,4)) + (m1(1,2) * m2(2,4))) + (m1(1,3) * m2(3,4))) + (m1(1,4) * m2(4,4));
	float num21 = (((m1(2,1) * m2(1,1)) + (m1(2,2) * m2(2,1))) + (m1(2,3) * m2(3,1))) + (m1(2,4) * m2(4,1));
	float num22 = (((m1(2,1) * m2(1,2)) + (m1(2,2) * m2(2,2))) + (m1(2,3) * m2(3,2))) + (m1(2,4) * m2(4,2));
	float num23 = (((m1(2,1) * m2(1,3)) + (m1(2,2) * m2(2,3))) + (m1(2,3) * m2(3,3))) + (m1(2,4) * m2(4,3));
	float num24 = (((m1(2,1) * m2(1,4)) + (m1(2,2) * m2(2,4))) + (m1(2,3) * m2(3,4))) + (m1(2,4) * m2(4,4));
	float num31 = (((m1(3,1) * m2(1,1)) + (m1(3,2) * m2(2,1))) + (m1(3,3) * m2(3,1))) + (m1(3,4) * m2(4,1));
	float num32 = (((m1(3,1) * m2(1,2)) + (m1(3,2) * m2(2,2))) + (m1(3,3) * m2(3,2))) + (m1(3,4) * m2(4,2));
	float num33 = (((m1(3,1) * m2(1,3)) + (m1(3,2) * m2(2,3))) + (m1(3,3) * m2(3,3))) + (m1(3,4) * m2(4,3));
	float num34 = (((m1(3,1) * m2(1,4)) + (m1(3,2) * m2(2,4))) + (m1(3,3) * m2(3,4))) + (m1(3,4) * m2(4,4));
	float num41 = (((m1(4,1) * m2(1,1)) + (m1(4,2) * m2(2,1))) + (m1(4,3) * m2(3,1))) + (m1(4,4) * m2(4,1));
	float num42 = (((m1(4,1) * m2(1,2)) + (m1(4,2) * m2(2,2))) + (m1(4,3) * m2(3,2))) + (m1(4,4) * m2(4,2));
	float num43 = (((m1(4,1) * m2(1,3)) + (m1(4,2) * m2(2,3))) + (m1(4,3) * m2(3,3))) + (m1(4,4) * m2(4,3));
	float num44 = (((m1(4,1) * m2(1,4)) + (m1(4,2) * m2(2,4))) + (m1(4,3) * m2(3,4))) + (m1(4,4) * m2(4,4));
	result(1,1) = num11;
	result(1,2) = num12;
	result(1,3) = num13;
	result(1,4) = num14;
	result(2,1) = num21;
	result(2,2) = num22;
	result(2,3) = num23;
	result(2,4) = num24;
	result(3,1) = num31;
	result(3,2) = num32;
	result(3,3) = num33;
	result(3,4) = num34;
	result(4,1) = num41;
	result(4,2) = num42;
	result(4,3) = num43;
	result(4,4) = num44;
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

void Matrix::Subtract(const Matrix &m1, const Matrix &m2, Matrix &result)
{
	result(1,1) = m1(1,1) - m2(1,1);
	result(1,2) = m1(1,2) - m2(1,2);
	result(1,3) = m1(1,3) - m2(1,3);
	result(1,4) = m1(1,4) - m2(1,4);
	result(2,1) = m1(2,1) - m2(2,1);
	result(2,2) = m1(2,2) - m2(2,2);
	result(2,3) = m1(2,3) - m2(2,3);
	result(2,4) = m1(2,4) - m2(2,4);
	result(3,1) = m1(3,1) - m2(3,1);
	result(3,2) = m1(3,2) - m2(3,2);
	result(3,3) = m1(3,3) - m2(3,3);
	result(3,4) = m1(3,4) - m2(3,4);
	result(4,1) = m1(4,1) - m2(4,1);
	result(4,2) = m1(4,2) - m2(4,2);
	result(4,3) = m1(4,3) - m2(4,3);
	result(4,4) = m1(4,4) - m2(4,4);
}

bool Matrix::Decompose(Vector3 &scale, Quaternion &rotation, Vector3 &translation)
{
	translation.X = m41;
	translation.Y = m42;
	translation.Z = m43;

	float xs = (MathHelper::Sign(m11 * m12 * m13 * m14) < 0.0f) ? -1.0f : 1.0f;
	float ys = (MathHelper::Sign(m21 * m22 * m23 * m24) < 0.0f) ? -1.0f : 1.0f;
	float zs = (MathHelper::Sign(m31 * m32 * m33 * m34) < 0.0f) ? -1.0f : 1.0f;                               

	scale.X = xs * (float)sqrt(m11 * m11 + m12 * m12 + m13 * m13);
	scale.Y = ys * (float)sqrt(m21 * m21 + m22 * m22 + m23 * m23);
	scale.Z = zs * (float)sqrt(m31 * m31 + m32 * m32 + m33 * m33);

	if (scale.X == 0.0 || scale.Y == 0.0 || scale.Z == 0.0)
	{
		rotation = Quaternion::Identity;
		return false;
	}

	Matrix m1(
		m11/scale.X, m12/scale.X, m13/scale.X, 0.0f,
		m21/scale.Y, m22/scale.Y, m23/scale.Y, 0.0f,
		m31/scale.Z, m32/scale.Z, m33/scale.Z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	rotation = Quaternion::CreateFromRotationMatrix(m1);
	return true;
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

Matrix Matrix::operator+= (const Matrix &op2)
{
	m11 += op2(1,1);
	m12 += op2(1,2);
	m13 += op2(1,3);
	m14 += op2(1,4);
	m21 += op2(2,1);
	m22 += op2(2,2);
	m23 += op2(2,3);
	m24 += op2(2,4);
	m31 += op2(3,1);
	m32 += op2(3,2);
	m33 += op2(3,3);
	m34 += op2(3,4);
	m41 += op2(4,1);
	m42 += op2(4,2);
	m43 += op2(4,3);
	m44 += op2(4,4);
	return *this;
}

Matrix Matrix::operator-= (const Matrix &op2)
{
	m11 -= op2(1,1);
	m12 -= op2(1,2);
	m13 -= op2(1,3);
	m14 -= op2(1,4);
	m21 -= op2(2,1);
	m22 -= op2(2,2);
	m23 -= op2(2,3);
	m24 -= op2(2,4);
	m31 -= op2(3,1);
	m32 -= op2(3,2);
	m33 -= op2(3,3);
	m34 -= op2(3,4);
	m41 -= op2(4,1);
	m42 -= op2(4,2);
	m43 -= op2(4,3);
	m44 -= op2(4,4);
	return *this;
}

Matrix Matrix::operator*= (const Matrix &op2)
{
	float temp11 = (((m11 * op2(1,1)) + (m12 * op2(2,1))) + (m13 * op2(3,1))) + (m14 * op2(4,1));
	float temp12 = (((m11 * op2(1,2)) + (m12 * op2(2,2))) + (m13 * op2(3,2))) + (m14 * op2(4,2));
	float temp13 = (((m11 * op2(1,3)) + (m12 * op2(2,3))) + (m13 * op2(3,3))) + (m14 * op2(4,3));
	float temp14 = (((m11 * op2(1,4)) + (m12 * op2(2,4))) + (m13 * op2(3,4))) + (m14 * op2(4,4));
	float temp21 = (((m21 * op2(1,1)) + (m22 * op2(2,1))) + (m23 * op2(3,1))) + (m24 * op2(4,1));
	float temp22 = (((m21 * op2(1,2)) + (m22 * op2(2,2))) + (m23 * op2(3,2))) + (m24 * op2(4,2));
	float temp23 = (((m21 * op2(1,3)) + (m22 * op2(2,3))) + (m23 * op2(3,3))) + (m24 * op2(4,3));
	float temp24 = (((m21 * op2(1,4)) + (m22 * op2(2,4))) + (m23 * op2(3,4))) + (m24 * op2(4,4));
	float temp31 = (((m31 * op2(1,1)) + (m32 * op2(2,1))) + (m33 * op2(3,1))) + (m34 * op2(4,1));
	float temp32 = (((m31 * op2(1,2)) + (m32 * op2(2,2))) + (m33 * op2(3,2))) + (m34 * op2(4,2));
	float temp33 = (((m31 * op2(1,3)) + (m32 * op2(2,3))) + (m33 * op2(3,3))) + (m34 * op2(4,3));
	float temp34 = (((m31 * op2(1,4)) + (m32 * op2(2,4))) + (m33 * op2(3,4))) + (m34 * op2(4,4));
	float temp41 = (((m41 * op2(1,1)) + (m42 * op2(2,1))) + (m43 * op2(3,1))) + (m44 * op2(4,1));
	float temp42 = (((m41 * op2(1,2)) + (m42 * op2(2,2))) + (m43 * op2(3,2))) + (m44 * op2(4,2));
	float temp43 = (((m41 * op2(1,3)) + (m42 * op2(2,3))) + (m43 * op2(3,3))) + (m44 * op2(4,3));
	float temp44 = (((m41 * op2(1,4)) + (m42 * op2(2,4))) + (m43 * op2(3,4))) + (m44 * op2(4,4));

	m11 = temp11;
	m12 = temp12;
	m13 = temp13;
	m14 = temp14;
	m21 = temp21;
	m22 = temp22;
	m23 = temp23;
	m24 = temp24;
	m31 = temp31;
	m32 = temp32;
	m33 = temp33;
	m34 = temp34;
	m41 = temp41;
	m42 = temp42;
	m43 = temp43;
	m44 = temp44;

	return *this;
}

Matrix Matrix::operator*= (float op2)
{
	m11 *= op2;
	m12 *= op2;
	m13 *= op2;
	m14 *= op2;
	m21 *= op2;
	m22 *= op2;
	m23 *= op2;
	m24 *= op2;
	m31 *= op2;
	m32 *= op2;
	m33 *= op2;
	m34 *= op2;
	m41 *= op2;
	m42 *= op2;
	m43 *= op2;
	m44 *= op2;
	return *this;
}

Matrix Matrix::operator/= (float op2)
{
	m11 /= op2;
	m12 /= op2;
	m13 /= op2;
	m14 /= op2;
	m21 /= op2;
	m22 /= op2;
	m23 /= op2;
	m24 /= op2;
	m31 /= op2;
	m32 /= op2;
	m33 /= op2;
	m34 /= op2;
	m41 /= op2;
	m42 /= op2;
	m43 /= op2;
	m44 /= op2;
	return *this;
}

Matrix operator+ (const Matrix &op1, const Matrix &op2)
{
	Matrix result;
	result(1,1) = op1(1,1) + op2(1,1);
	result(1,2) = op1(1,2) + op2(1,2);
	result(1,3) = op1(1,3) + op2(1,3);
	result(1,4) = op1(1,4) + op2(1,4);
	result(2,1) = op1(2,1) + op2(2,1);
	result(2,2) = op1(2,2) + op2(2,2);
	result(2,3) = op1(2,3) + op2(2,3);
	result(2,4) = op1(2,4) + op2(2,4);
	result(3,1) = op1(3,1) + op2(3,1);
	result(3,2) = op1(3,2) + op2(3,2);
	result(3,3) = op1(3,3) + op2(3,3);
	result(3,4) = op1(3,4) + op2(3,4);
	result(4,1) = op1(4,1) + op2(4,1);
	result(4,2) = op1(4,2) + op2(4,2);
	result(4,3) = op1(4,3) + op2(4,3);
	result(4,4) = op1(4,4) + op2(4,4);
	return result;
}

Matrix operator- (const Matrix &op1, const Matrix &op2)
{
	Matrix result;
	result(1,1) = op1(1,1) - op2(1,1);
	result(1,2) = op1(1,2) - op2(1,2);
	result(1,3) = op1(1,3) - op2(1,3);
	result(1,4) = op1(1,4) - op2(1,4);
	result(2,1) = op1(2,1) - op2(2,1);
	result(2,2) = op1(2,2) - op2(2,2);
	result(2,3) = op1(2,3) - op2(2,3);
	result(2,4) = op1(2,4) - op2(2,4);
	result(3,1) = op1(3,1) - op2(3,1);
	result(3,2) = op1(3,2) - op2(3,2);
	result(3,3) = op1(3,3) - op2(3,3);
	result(3,4) = op1(3,4) - op2(3,4);
	result(4,1) = op1(4,1) - op2(4,1);
	result(4,2) = op1(4,2) - op2(4,2);
	result(4,3) = op1(4,3) - op2(4,3);
	result(4,4) = op1(4,4) - op2(4,4);
	return result;
}

Matrix operator- (const Matrix &op1)
{
	Matrix result;
	result(1,1) = -op1(1,1);
	result(1,2) = -op1(1,2);
	result(1,3) = -op1(1,3);
	result(1,4) = -op1(1,4);
	result(2,1) = -op1(2,1);
	result(2,2) = -op1(2,2);
	result(2,3) = -op1(2,3);
	result(2,4) = -op1(2,4);
	result(3,1) = -op1(3,1);
	result(3,2) = -op1(3,2);
	result(3,3) = -op1(3,3);
	result(3,4) = -op1(3,4);
	result(4,1) = -op1(4,1);
	result(4,2) = -op1(4,2);
	result(4,3) = -op1(4,3);
	result(4,4) = -op1(4,4);
	return result;
}

Matrix operator* (const Matrix &op1, const Matrix &op2)
{
	Matrix result;
	result(1,1) = (((op1(1,1) * op2(1,1)) + (op1(1,2) * op2(2,1))) + (op1(1,3) * op2(3,1))) + (op1(1,4) * op2(4,1));
	result(1,2) = (((op1(1,1) * op2(1,2)) + (op1(1,2) * op2(2,2))) + (op1(1,3) * op2(3,2))) + (op1(1,4) * op2(4,2));
	result(1,3) = (((op1(1,1) * op2(1,3)) + (op1(1,2) * op2(2,3))) + (op1(1,3) * op2(3,3))) + (op1(1,4) * op2(4,3));
	result(1,4) = (((op1(1,1) * op2(1,4)) + (op1(1,2) * op2(2,4))) + (op1(1,3) * op2(3,4))) + (op1(1,4) * op2(4,4));
	result(2,1) = (((op1(2,1) * op2(1,1)) + (op1(2,2) * op2(2,1))) + (op1(2,3) * op2(3,1))) + (op1(2,4) * op2(4,1));
	result(2,2) = (((op1(2,1) * op2(1,2)) + (op1(2,2) * op2(2,2))) + (op1(2,3) * op2(3,2))) + (op1(2,4) * op2(4,2));
	result(2,3) = (((op1(2,1) * op2(1,3)) + (op1(2,2) * op2(2,3))) + (op1(2,3) * op2(3,3))) + (op1(2,4) * op2(4,3));
	result(2,4) = (((op1(2,1) * op2(1,4)) + (op1(2,2) * op2(2,4))) + (op1(2,3) * op2(3,4))) + (op1(2,4) * op2(4,4));
	result(3,1) = (((op1(3,1) * op2(1,1)) + (op1(3,2) * op2(2,1))) + (op1(3,3) * op2(3,1))) + (op1(3,4) * op2(4,1));
	result(3,2) = (((op1(3,1) * op2(1,2)) + (op1(3,2) * op2(2,2))) + (op1(3,3) * op2(3,2))) + (op1(3,4) * op2(4,2));
	result(3,3) = (((op1(3,1) * op2(1,3)) + (op1(3,2) * op2(2,3))) + (op1(3,3) * op2(3,3))) + (op1(3,4) * op2(4,3));
	result(3,4) = (((op1(3,1) * op2(1,4)) + (op1(3,2) * op2(2,4))) + (op1(3,3) * op2(3,4))) + (op1(3,4) * op2(4,4));
	result(4,1) = (((op1(4,1) * op2(1,1)) + (op1(4,2) * op2(2,1))) + (op1(4,3) * op2(3,1))) + (op1(4,4) * op2(4,1));
	result(4,2) = (((op1(4,1) * op2(1,2)) + (op1(4,2) * op2(2,2))) + (op1(4,3) * op2(3,2))) + (op1(4,4) * op2(4,2));
	result(4,3) = (((op1(4,1) * op2(1,3)) + (op1(4,2) * op2(2,3))) + (op1(4,3) * op2(3,3))) + (op1(4,4) * op2(4,3));
	result(4,4) = (((op1(4,1) * op2(1,4)) + (op1(4,2) * op2(2,4))) + (op1(4,3) * op2(3,4))) + (op1(4,4) * op2(4,4));
	return result;
}

Vector3 operator* (const Matrix &op1, const Vector3 &op2)
{
	Vector3 result;
	result.X = op2.X * op1(0,0) + op2.Y * op1(0,1) + op2.Z * op1(0,2) + op1(0,3);
	result.Y = op2.X * op1(1,0) + op2.Y * op1(1,1) + op2.Z * op1(1,2) + op1(1,3);
	result.Z = op2.X * op1(2,0) + op2.Y * op1(2,1) + op2.Z * op1(2,2) + op1(2,3);
	return result;
}

Matrix operator* (const Matrix &op1, float op2)
{
	Matrix result;
	result(1,1) = op1(1,1) * op2;
	result(1,2) = op1(1,2) * op2;
	result(1,3) = op1(1,3) * op2;
	result(1,4) = op1(1,4) * op2;
	result(2,1) = op1(2,1) * op2;
	result(2,2) = op1(2,2) * op2;
	result(2,3) = op1(2,3) * op2;
	result(2,4) = op1(2,4) * op2;
	result(3,1) = op1(3,1) * op2;
	result(3,2) = op1(3,2) * op2;
	result(3,3) = op1(3,3) * op2;
	result(3,4) = op1(3,4) * op2;
	result(4,1) = op1(4,1) * op2;
	result(4,2) = op1(4,2) * op2;
	result(4,3) = op1(4,3) * op2;
	result(4,4) = op1(4,4) * op2;
	return result;
}

Matrix operator* (float op1, const Matrix &op2)
{
	Matrix result;
	result(1,1) = op2(1,1) * op1;
	result(1,2) = op2(1,2) * op1;
	result(1,3) = op2(1,3) * op1;
	result(1,4) = op2(1,4) * op1;
	result(2,1) = op2(2,1) * op1;
	result(2,2) = op2(2,2) * op1;
	result(2,3) = op2(2,3) * op1;
	result(2,4) = op2(2,4) * op1;
	result(3,1) = op2(3,1) * op1;
	result(3,2) = op2(3,2) * op1;
	result(3,3) = op2(3,3) * op1;
	result(3,4) = op2(3,4) * op1;
	result(4,1) = op2(4,1) * op1;
	result(4,2) = op2(4,2) * op1;
	result(4,3) = op2(4,3) * op1;
	result(4,4) = op2(4,4) * op1;
	return result;
}

Matrix operator/ (const Matrix &op1, const Matrix &op2)
{
	Matrix result;
	result(1,1) = op1(1,1) / op2(1,1);
	result(1,2) = op1(1,2) / op2(1,2);
	result(1,3) = op1(1,3) / op2(1,3);
	result(1,4) = op1(1,4) / op2(1,4);
	result(2,1) = op1(2,1) / op2(2,1);
	result(2,2) = op1(2,2) / op2(2,2);
	result(2,3) = op1(2,3) / op2(2,3);
	result(2,4) = op1(2,4) / op2(2,4);
	result(3,1) = op1(3,1) / op2(3,1);
	result(3,2) = op1(3,2) / op2(3,2);
	result(3,3) = op1(3,3) / op2(3,3);
	result(3,4) = op1(3,4) / op2(3,4);
	result(4,1) = op1(4,1) / op2(4,1);
	result(4,2) = op1(4,2) / op2(4,2);
	result(4,3) = op1(4,3) / op2(4,3);
	result(4,4) = op1(4,4) / op2(4,4);
	return result;
}

Matrix operator/ (const Matrix &op1, float op2)
{
	Matrix result;
	result(1,1) = op1(1,1) / op2;
	result(1,2) = op1(1,2) / op2;
	result(1,3) = op1(1,3) / op2;
	result(1,4) = op1(1,4) / op2;
	result(2,1) = op1(2,1) / op2;
	result(2,2) = op1(2,2) / op2;
	result(2,3) = op1(2,3) / op2;
	result(2,4) = op1(2,4) / op2;
	result(3,1) = op1(3,1) / op2;
	result(3,2) = op1(3,2) / op2;
	result(3,3) = op1(3,3) / op2;
	result(3,4) = op1(3,4) / op2;
	result(4,1) = op1(4,1) / op2;
	result(4,2) = op1(4,2) / op2;
	result(4,3) = op1(4,3) / op2;
	result(4,4) = op1(4,4) / op2;
	return result;
}

}
