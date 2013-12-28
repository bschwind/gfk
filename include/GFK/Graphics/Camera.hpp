#pragma once

#include <GFK/Math/Matrix.hpp>

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
};

}
