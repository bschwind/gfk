#include <GFK/Graphics/Camera2D.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>

namespace gfk
{

Camera2D::Camera2D() :
Camera()
{

}

Camera2D::~Camera2D()
{

}

Matrix Camera2D::GetView()
{
	Matrix::CreateLookAt(pos, pos + Vector3(0, 0, -1.0f), Vector3::Up, view);
	return view;
}

Matrix Camera2D::GetProjection()
{
	Matrix::CreateOrthographicUpperLeftOrigin(screenWidth, screenHeight, 0.0f, 100.0f, projection);
	return projection;
}

void Camera2D::SetPos(const Vector3 &position)
{
	pos = position;
}

}
