#include "TopDownCamera.hpp"
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>

namespace gfk
{

TopDownCamera::TopDownCamera() :
Camera(),
pos(Vector3::Zero)
{

}

TopDownCamera::~TopDownCamera()
{

}

Matrix TopDownCamera::GetView()
{
	Matrix::CreateLookAt(pos + Vector3(0.5f, 0.5f, 0.5f), pos, Vector3(0, 1.0f, 0), view);
	return view;
}

Matrix TopDownCamera::GetProjection()
{
	Matrix::CreateOrthographic(screenWidth * 0.04f, screenHeight * 0.04f, 0.0f, 500.0f, projection);
	return projection;
}

void TopDownCamera::SetPos(const Vector3 &position)
{
	pos = position;
}

}
