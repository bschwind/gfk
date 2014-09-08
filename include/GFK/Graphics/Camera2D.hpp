#pragma once

#include <GFK/Graphics/Camera.hpp>
#include <GFK/Math/Vector3.hpp>

namespace gfk
{

class Camera2D : public Camera
{
public:
	Camera2D();
	~Camera2D();

	Matrix GetView();
	Matrix GetProjection();
	void SetPos(const Vector3 &position);
private:
	Vector3 pos;
};

}
