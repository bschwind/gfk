#pragma once

#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/Vector3.hpp>

namespace gfk
{

class Camera
{
public:
	virtual Matrix GetView();
	virtual Matrix GetProjection();
	virtual void Update(float dt);
protected:
	Matrix view;
	Matrix projection;
private:
	Vector3 pos;
	float totalTime = 0.0f;
};

}
