#include <GFK/Graphics/Camera2D.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>

namespace gfk
{

Camera2D::Camera2D() :
screenWidth(0.0f),
screenHeight(0.0f)
{

}

Camera2D::~Camera2D()
{

}

Matrix Camera2D::GetView()
{
	Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3::Up, view);
	return view;
}

Matrix Camera2D::GetProjection()
{
	Matrix::CreateOrthographicUpperLeftOrigin(screenWidth, screenHeight, 0.0f, 1.0f, projection);
	return projection;
}

void Camera2D::Update(float dt)
{

}

}
