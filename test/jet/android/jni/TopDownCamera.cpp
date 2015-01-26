#include "TopDownCamera.hpp"
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>

namespace gfk
{

TopDownCamera::TopDownCamera() :
Camera()
{

}

TopDownCamera::~TopDownCamera()
{

}

Matrix TopDownCamera::GetView()
{
	Matrix::CreateLookAt(Vector3(0.5f, 0.5f, 0.5f), Vector3(0, 0, 0), Vector3(0, 1.0f, 0), view);
	return view;
}

Matrix TopDownCamera::GetProjection()
{
	Matrix::CreateOrthographic(screenWidth * 0.08f, screenHeight * 0.08f, 0.0f, 100.0f, projection);
	return projection;
}

void TopDownCamera::SetPos(const Vector3 &position)
{
	pos = position;
}

}
