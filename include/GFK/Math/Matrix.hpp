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

	static Matrix CreateBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &cameraUpVector, const Vector3 &cameraForwardVector);
	static void CreateBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &cameraUpVector, const Vector3 &cameraForwardVector, Matrix &result);
	static Matrix CreateConstrainedBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &rotateAxis, const Vector3 &cameraForwardVector, const Vector3 &objectForwardVector);
	static void CreateConstrainedBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &rotateAxis, const Vector3 &cameraForwardVector, const Vector3 &objectForwardVector, Matrix &result);
	static Matrix CreateFromAxisAngle(const Vector3 &axis, const float angle);
	static void CreateFromAxisAngle(const Vector3 &axis, const float angle, Matrix &result);
	//static Matrix CreateFromQuaternion(Quaternion quaternion);
	// static Matrix CreateFromYawPitchRoll(const float yaw, const float pitch, const float roll);
	// static void CreateFromYawPitchRoll(const float yaw, const float pitch, const float roll, Matrix result);
	static Matrix CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);
	static void CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector, Matrix &result);
	static Matrix CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane);
	static void CreateOrthographic(const float width, const float height, const float zNearPlane, const float zFarPlane, Matrix &result);
	static Matrix CreateOrthographicOffCenter(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane);
	static void CreateOrthographicOffCenter(const float left, const float right, const float bottom, const float top, const float zNearPlane, const float zFarPlane, Matrix &result);
	static Matrix CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance);
	static void CreatePerspective(const float width, const float height, const float nearPlaneDistance, const float farPlaneDistance, Matrix &result);
	static Matrix CreatePerspectiveFieldOfView(const float fieldOfView, const float aspectRatio, const float nearPlaneDistance, const float farPlaneDistance);
	static void CreatePerspectiveFieldOfView(const float fieldOfView, const float aspectRatio, const float nearPlaneDistance, const float farPlaneDistance, Matrix &result);
	static Matrix CreatePerspectiveOffCenter(const float left, const float right, const float bottom, const float top, const float nearPlaneDistance, const float farPlaneDistance);
	static void CreatePerspectiveOffCenter(const float left, const float right, const float bottom, const float top, const float nearPlaneDistance, const float farPlaneDistance, Matrix &result);
	static Matrix CreateRotationX(const float radians);
	static void CreateRotationX(const float radians, Matrix &result);
	static Matrix CreateRotationY(const float radians);
	static void CreateRotationY(const float radians, Matrix &result);
	static Matrix CreateRotationZ(const float radians);
	static void CreateRotationZ(const float radians, Matrix &result);
	static Matrix CreateScale(const float scale);
	static void CreateScale(const float scale, Matrix &result);
	static Matrix CreateScale(const float xScale, const float yScale, const float zScale);
	static void CreateScale(const float xScale, const float yScale, const float zScale, Matrix &result);
	static Matrix CreateScale(Vector3 scales);
	static void CreateScale(Vector3 scales, Matrix &result);
	static Matrix CreateTranslation(const float xPosition, const float yPosition, const float zPosition);
	static void CreateTranslation(const float xPosition, const float yPosition, const float zPosition, Matrix &result);
	static Matrix CreateTranslation(const Vector3 position);
	static void CreateTranslation(const Vector3 position, Matrix &result);
	//static Matrix CreateReflection(Plane value);
	//static Matrix CreateReflection(Plane value, Matrix &result);
	static Matrix CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up);
	static void CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up, Matrix &result);
	static Matrix Invert(const Matrix &matrix);
	static void Invert(const Matrix &matrix, Matrix &result);
	static Matrix Lerp(const Matrix &matrix1, const Matrix &matrix2, const float amount);
	static void Lerp(const Matrix &matrix1, const Matrix &matrix2, const float amount, Matrix &result);
	static Matrix Negate(const Matrix &matrix);
	static void Negate(const Matrix &matrix, Matrix &result);
	static Matrix Transpose(const Matrix &matrix);
	static void Transpose(const Matrix &matrix, Matrix &result);

	float *ToFloatArray () const { return (float *)&(matrix[0]); }
	float Determinant();
	Vector3 GetBackward();
	Vector3 GetForward();
	void SetForward(const Vector3 &v);
	Vector3 GetRight();
	void SetRight(const Vector3 &v);
	Vector3 GetLeft();
	Vector3 GetUp();
	void SetUp(const Vector3 &v);
	Vector3 GetDown();
	Vector3 GetTranslation();
	void SetTranslation(const Vector3 &v);

	float &operator()(int row, int column) { return matrix[column * 4 + row]; }
	const float &operator()(int row, int column) const { return matrix[column * 4 + row]; }
protected:
private:
	float matrix[16];
};

}