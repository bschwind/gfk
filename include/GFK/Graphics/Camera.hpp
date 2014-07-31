#pragma once

#include <GFK/Math/Matrix.hpp>

namespace gfk
{

class Camera
{
public:
	Camera();
	~Camera();
	virtual Matrix GetView();
	virtual Matrix GetProjection();

	void SetScreenWidth(int screenWidth);
	void SetScreenHeight(int screenHeight);
protected:
	Matrix view;
	Matrix projection;
	int screenWidth, screenHeight;
private:
};

}
