#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/MathHelper.hpp>
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

}