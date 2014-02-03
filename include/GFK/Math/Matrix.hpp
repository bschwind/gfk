#pragma once

namespace gfk
{

class Vector3;
class Quaternion;

class Matrix
{
// Matrix Format
//
// |0  4  8  12|
// |1  5  9  13|
// |2  6  10 14|
// |3  7  11 15|

public:
	Matrix();
	Matrix(
		float M11, float M12, float M13, float M14,
		float M21, float M22, float M23, float M24,
		float M31, float M32, float M33, float M34,
		float M41, float M42, float M43, float M44);
	~Matrix();

	static const Matrix Identity;

	static void Add(const Matrix &m1, const Matrix &m2, Matrix &result);
	static Matrix CreateBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &cameraUpVector, const Vector3 &cameraForwardVector);
	static void CreateBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &cameraUpVector, const Vector3 &cameraForwardVector, Matrix &result);
	static Matrix CreateConstrainedBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &rotateAxis, const Vector3 &cameraForwardVector, const Vector3 &objectForwardVector);
	static void CreateConstrainedBillboard(const Vector3 &objectPosition, const Vector3 &cameraPosition, const Vector3 &rotateAxis, const Vector3 &cameraForwardVector, const Vector3 &objectForwardVector, Matrix &result);
	static Matrix CreateFromAxisAngle(const Vector3 &axis, float angle);
	static void CreateFromAxisAngle(const Vector3 &axis, float angle, Matrix &result);
	static Matrix CreateFromQuaternion(const Quaternion &quaternion);
	static void CreateFromQuaternion(const Quaternion &quaternion, Matrix &result);
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Matrix result);
	static Matrix CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector);
	static void CreateLookAt(const Vector3 &cameraPosition, const Vector3 &cameraTarget, const Vector3 &cameraUpVector, Matrix &result);
	static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
	static void CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane, Matrix &result);
	static Matrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);
	static void CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane, Matrix &result);
	static Matrix CreateOrthographicUpperLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance);
	static void CreateOrthographicUpperLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance, Matrix &result);
	static Matrix CreateOrthographicBottomLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance);
	static void CreateOrthographicBottomLeftOrigin(float screenWidth, float screenHeight, float nearPlaneDistance, float farPlaneDistance, Matrix &result);
	static Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
	static void CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance, Matrix &result);
	static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
	static void CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance, Matrix &result);
	static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);
	static void CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance, Matrix &result);
	static Matrix CreateRotationX(float radians);
	static void CreateRotationX(float radians, Matrix &result);
	static Matrix CreateRotationY(float radians);
	static void CreateRotationY(float radians, Matrix &result);
	static Matrix CreateRotationZ(float radians);
	static void CreateRotationZ(float radians, Matrix &result);
	static Matrix CreateScale(float scale);
	static void CreateScale(float scale, Matrix &result);
	static Matrix CreateScale(float xScale, float yScale, float zScale);
	static void CreateScale(float xScale, float yScale, float zScale, Matrix &result);
	static Matrix CreateScale(const Vector3 &scales);
	static void CreateScale(const Vector3 &scales, Matrix &result);
	static Matrix CreateTranslation(float xPosition, float yPosition, float zPosition);
	static void CreateTranslation(float xPosition, float yPosition, float zPosition, Matrix &result);
	static Matrix CreateTranslation(const Vector3 &position);
	static void CreateTranslation(const Vector3 &position, Matrix &result);
	// static Matrix CreateReflection(Plane value);
	// static Matrix CreateReflection(Plane value, Matrix &result);
	static Matrix CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up);
	static void CreateWorld(const Vector3 &position, const Vector3 &forward, const Vector3 &up, Matrix &result);
	static void Divide(const Matrix &m, float divisor, Matrix &result);
	static void Divide(const Matrix &m1, const Matrix &m2, Matrix &result);
	static Matrix Invert(const Matrix &matrix);
	static void Invert(const Matrix &matrix, Matrix &result);
	static Matrix Lerp(const Matrix &matrix1, const Matrix &matrix2, float amount);
	static void Lerp(const Matrix &matrix1, const Matrix &matrix2, float amount, Matrix &result);
	static void Multiply(const Matrix &m, float scalar, Matrix &result);
	static void Multiply(const Matrix &m1, const Matrix &m2, Matrix &result);
	static Matrix Negate(const Matrix &matrix);
	static void Negate(const Matrix &matrix, Matrix &result);
	static Matrix Transpose(const Matrix &matrix);
	static void Transpose(const Matrix &matrix, Matrix &result);
	static void Subtract(const Matrix &m1, const Matrix &m2, Matrix &result);

	float *ToFloatArray () const { return (float *)&(matrix[0]); }
	bool Decompose(Vector3 &scale, Quaternion &rotation, Vector3 &translation);
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

	float &operator()(int row, int column) { return matrix[(column-1) * 4 + (row-1)]; }
	const float &operator()(int row, int column) const { return matrix[(column-1) * 4 + (row-1)]; }

	Matrix operator+= (const Matrix &op2);
	Matrix operator-= (const Matrix &op2);
	Matrix operator*= (const Matrix &op2);
	Matrix operator*= (float op2);
	Matrix operator/= (float divisor);
protected:
private:
	float matrix[16];
};

Matrix operator+ (const Matrix &op1, const Matrix &op2);
Matrix operator- (const Matrix &op1, const Matrix &op2);
Matrix operator- (const Matrix &op1);
Matrix operator* (const Matrix &op1, const Matrix &op2);
Vector3 operator* (const Matrix &op1, const Vector3 &op2);
Matrix operator* (const Matrix &op1, float op2);
Matrix operator* (float op1, const Matrix &op2);
Matrix operator/ (const Matrix &op1, const Matrix &op2);
Matrix operator/ (const Matrix &op1, float op2);

}