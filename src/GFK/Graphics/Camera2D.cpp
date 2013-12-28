#include <GFK/Graphics/Camera2D.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>

namespace gfk
{

Matrix Camera2D::GetView()
{
	Matrix::CreateLookAt(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3::Up, view);
	return view;
}

Matrix Camera2D::GetProjection()
{
	Matrix::CreateOrthographic(1280, 720, 0.1f, 100, projection);
	return projection;
}

void Camera2D::Update(float dt)
{

}

}
