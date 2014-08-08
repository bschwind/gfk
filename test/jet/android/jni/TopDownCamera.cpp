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
	Matrix::CreateLookAt(pos, pos + Vector3(0, -1.0f, 0), Vector3(0, 0, -1.0f), view);
	return view;
}

Matrix TopDownCamera::GetProjection()
{
	Matrix::CreateOrthographic(screenWidth * 0.01f, screenHeight * 0.01f, 0.0f, 100.0f, projection);
	return projection;
}

void TopDownCamera::SetPos(const Vector3 &position)
{
	pos = position;
}

}
