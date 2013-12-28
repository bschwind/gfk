#include <GFK/Graphics/Camera.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>

namespace gfk
{

Matrix Camera::GetView()
{
	Matrix::CreateLookAt(Vector3(30, 40, 100), Vector3(0, 0, 0), Vector3::Up, view);
	return view;
}

Matrix Camera::GetProjection()
{
	Matrix::CreatePerspectiveFieldOfView(MathHelper::Pi * 0.25f, 1280.0f / 720.0f, 0.1f, 1000.0f, projection);
	return projection;
}

void Camera::Update(float dt)
{

}

}
