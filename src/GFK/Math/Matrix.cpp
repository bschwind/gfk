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

Vector3 Matrix::GetBackward()
{
	return Vector3(m31, m32, m33);
}

Vector3 Matrix::GetForward()
{
	return Vector3(-m31, -m32, -m33);
}

Vector3 Matrix::GetRight()
{
	return Vector3(m11, m12, m13);
}

Vector3 Matrix::GetLeft()
{
	return Vector3(-m11, -m12, -m13);
}

Vector3 Matrix::GetUp()
{
	return Vector3(m21, m22, m23);
}

Vector3 Matrix::GetDown()
{
	return Vector3(-m21, -m22, -m23);
}

Vector3 Matrix::GetTranslation()
{
	return Vector3(m41, m42, m43);
}

// Matrix CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Nullable<Vector3> cameraForwardVector)
// {
// 	 Vector3 vector;
//             Vector3 vector2;
//             Vector3 vector3;
//             vector.X = objectPosition.X - cameraPosition.X;
//             vector.Y = objectPosition.Y - cameraPosition.Y;
//             vector.Z = objectPosition.Z - cameraPosition.Z;
//             float num = vector.LengthSquared();
//             if (num < 0.0001f)
//             {
//                 vector = cameraForwardVector.HasValue ? -cameraForwardVector.Value : Vector3.Forward;
//             }
//             else
//             {
//                 Vector3.Multiply(ref vector, (float)(1f / ((float)Math.Sqrt((double)num))), out vector);
//             }
//             Vector3.Cross(ref cameraUpVector, ref vector, out vector3);
//             vector3.Normalize();
//             Vector3.Cross(ref vector, ref vector3, out vector2);
//             result.M11 = vector3.X;
//             result.M12 = vector3.Y;
//             result.M13 = vector3.Z;
//             result.M14 = 0f;
//             result.M21 = vector2.X;
//             result.M22 = vector2.Y;
//             result.M23 = vector2.Z;
//             result.M24 = 0f;
//             result.M31 = vector.X;
//             result.M32 = vector.Y;
//             result.M33 = vector.Z;
//             result.M34 = 0f;
//             result.M41 = objectPosition.X;
//             result.M42 = objectPosition.Y;
//             result.M43 = objectPosition.Z;
//             result.M44 = 1f;
// }

}
