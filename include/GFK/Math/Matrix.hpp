#pragma once

namespace gfk
{

class Matrix
{
public:
	Matrix();
	Matrix(
		const float M11, const float M12, const float M13, const float M14,
		const float M21, const float M22, const float M23, const float M24,
		const float M31, const float M32, const float M33, const float M34,
		const float M41, const float M42, const float M43, const float M44);
	~Matrix();

	static const Matrix Identity;

	float *ToFloatArray () const { return (float *)&(matrix[0]); }
protected:
private:
	float matrix[16];
};

}