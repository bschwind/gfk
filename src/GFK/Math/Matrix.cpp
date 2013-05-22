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
	result.SetBackward(vector);
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
	result.SetBackward(vector);
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

Vector3 Matrix::GetBackward()
{
	return Vector3(m31, m32, m33);
}

void Matrix::SetBackward(const Vector3 &v)
{
	m31 = v.X;
	m32 = v.Y;
	m33 = v.Z;
}

Vector3 Matrix::GetForward()
{
	return Vector3(-m31, -m32, -m33);
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
