#pragma once

#include <GFK/Graphics/Camera.hpp>
#include <GFK/Math/Vector3.hpp>

namespace gfk
{

class TopDownCamera : public Camera
{
public:
	TopDownCamera();
	~TopDownCamera();

	Matrix GetView();
	Matrix GetProjection();
	void SetPos(const Vector3 &position);
private:
	Vector3 pos;
	float yRot;
	float xRot;
};

}
