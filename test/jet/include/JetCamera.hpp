#pragma once

#include <GFK/Graphics/Camera.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/Math/Vector3.hpp>

using namespace gfk;

namespace jetGame
{

class JetCamera : public Camera
{
public:
	JetCamera();
	JetCamera(const Vector3 &initialPos);
	~JetCamera();
	Matrix GetView();
	Matrix GetProjection();
	void Update(float dt, const Vector3 &forward, const Vector3 &up, const Vector3 &right);
	void SetPos(const Vector3 &position);
private:
	Vector3 forward, up, right;
	Vector3 pos;
};

}
