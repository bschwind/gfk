#pragma once

#include <GFK/Graphics/Camera.hpp>

namespace gfk
{

class Camera2D : public Camera
{
public:
	Camera2D();
	~Camera2D();

	float screenWidth, screenHeight;

	Matrix GetView();
	Matrix GetProjection();
	void Update(float dt);
};

}
