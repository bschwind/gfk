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

	float *ToFloatArray () const { return (float *)&(matrix[0]); }
	Vector3 GetBackward();
	void SetBackward(const Vector3 &v);
	Vector3 GetForward();
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