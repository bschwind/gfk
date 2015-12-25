#include "JetCamera.hpp"
#include <GFK/Math/MathHelper.hpp>

using namespace gfk;

namespace jetGame
{

JetCamera::JetCamera() :
Camera()
{

}

JetCamera::JetCamera(const Vector3 &initialPos) :
Camera(),
pos(initialPos)
{

}

JetCamera::~JetCamera()
{

}

Matrix JetCamera::GetView()
{
	Matrix::CreateLookAt(pos, pos + forward * 10, up, view);
	return view;
}

Matrix JetCamera::GetProjection()
{
	Matrix::CreatePerspectiveFieldOfView(MathHelper::Pi * 0.25f, screenWidth / (float)screenHeight, 0.1f, 1000.0f, projection);
	return projection;
}

void JetCamera::Update(float dt, const Vector3 &f, const Vector3 &u, const Vector3 &r)
{
	forward = f;
	up = u;
	right = r;
}

void JetCamera::SetPos(const Vector3 &position)
{
	pos = position;
}

}
