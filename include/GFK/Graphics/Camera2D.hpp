#pragma once

#include <GFK/Graphics/Camera.hpp>

namespace gfk
{

class Camera2D : public Camera
{
public:
	Matrix GetView();
	Matrix GetProjection();
	void Update(float dt);
};

}
