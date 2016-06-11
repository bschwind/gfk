#include "TopDownCamera.hpp"
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Math/Quaternion.hpp>

namespace gfk
{

TopDownCamera::TopDownCamera() :
Camera(),
pos(Vector3::Zero),
yRot(0.785f),
xRot(1.2f)
{

}

TopDownCamera::~TopDownCamera()
{

}

Matrix TopDownCamera::GetView()
{
	Quaternion yQuat = Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), yRot);
	Quaternion xQuat = Quaternion::CreateFromAxisAngle(Vector3(1, 0, 0), xRot);

	Matrix::CreateLookAt(pos + Vector3::Transform(Vector3(0, 1, 0), yQuat * xQuat) * 15, pos, Vector3::Transform(Vector3(0, 0, -1.0f), yQuat * xQuat) * 15, view);
	// Matrix::CreateLookAt(pos + Vector3(0.5f, 0.5f, 0.5f) * 100, pos, Vector3(0, 1.0f, 0), view);
	return view;
}

Matrix TopDownCamera::GetProjection()
{
	Matrix::CreateOrthographic(screenWidth * 0.004f, screenHeight * 0.004f, 0.0f, 500.0f, projection);
	// Matrix::CreatePerspectiveFieldOfView(MathHelper::Pi * 0.25f, screenWidth / (float)screenHeight, 0.1f, 1000.0f, projection);
	return projection;
}

void TopDownCamera::SetPos(const Vector3 &position)
{
	pos = position;
}

void TopDownCamera::SetYRot(float rot)
{
	yRot = rot;
}

}
