#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Math/Vector3.hpp>
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

void CreateBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &cameraUpVector, const Vector3 &cameraForwardVector, Matrix &result)
{
	Vector3 vector(0.0f);
	Vector3 vector2(0.0f);
	Vector3 vector3(0.0f);
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
