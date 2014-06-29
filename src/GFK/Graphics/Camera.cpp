#include <GFK/OSDetection.hpp>
#include <GFK/Graphics/Camera.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>
#if !defined(PLATFORM_ANDROID)
	#include <GFK/Input/Keyboard.hpp>
#endif
#include <iostream>
#include <cmath>

namespace gfk
{

Camera::Camera() :
pos(Vector3(-30, 10, 0))
{

}

Camera::~Camera()
{

}

Matrix Camera::GetView()
{
	Matrix::CreateLookAt(pos, Vector3(0, 0, 0), Vector3::Up, view);
	return view;
}

Matrix Camera::GetProjection()
{
	Matrix::CreatePerspectiveFieldOfView(MathHelper::Pi * 0.25f, screenWidth / screenHeight, 0.1f, 1000.0f, projection);
	return projection;
}

void Camera::Update(float dt)
{
	pos.Z = 0;
#if !defined(PLATFORM_ANDROID)
	if (Keyboard::IsKeyDown(Keys::Left))
	{
		pos.X -= 50 * dt;
	}

	if (Keyboard::IsKeyDown(Keys::Right))
	{
		pos.X += 50 * dt;
	}

	if (Keyboard::IsKeyDown(Keys::Up))
	{
		pos.Y += 10 * dt;
	}

	if (Keyboard::IsKeyDown(Keys::Down))
	{
		pos.Y -= 10 * dt;
	}
#endif
}

}
