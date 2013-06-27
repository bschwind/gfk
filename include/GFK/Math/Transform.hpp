#pragma once

#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>

namespace gfk
{

class Transform
{
public:
	Vector3 Scale;
	Quaternion Rotation;
	Vector3 Position;
protected:
private:
};

}