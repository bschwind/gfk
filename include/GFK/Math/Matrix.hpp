#pragma once
#include <GFK/Math/Vector3.hpp>

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
	Vector3 GetBackward();
	Vector3 GetForward();
	Vector3 GetRight();
	Vector3 GetLeft();
	Vector3 GetUp();
	Vector3 GetDown();
	Vector3 GetTranslation();
	// Matrix CreateBillboard(const Vector3 objectPosition, const Vector3 cameraPosition, const Vector3 cameraUpVector, const Vector3 cameraForwardVector);
	// void CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition, Vector3 cameraUpVector, Nullable<Vector3> cameraForwardVector, Vector3 result); 
protected:
private:
	float matrix[16];
};

}