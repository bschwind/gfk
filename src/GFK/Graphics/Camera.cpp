#include <GFK/Graphics/Camera.hpp>
#include <GFK/Math/Matrix.hpp>

namespace gfk
{

Camera::Camera()
{

}

Camera::~Camera()
{

}

Matrix Camera::GetView()
{
	return view;
}

Matrix Camera::GetProjection()
{
	return projection;
}

void Camera::SetScreenWidth(int width)
{
	screenWidth = width;
}

void Camera::SetScreenHeight(int height)
{
	screenHeight = height;
}

}
