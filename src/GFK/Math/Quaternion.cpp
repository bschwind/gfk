#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Math/Vector3.hpp>
#include <cmath>

namespace gfk
{
	
Quaternion::Quaternion() :
X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
{

}

Quaternion::Quaternion(float x, float y, float z, float w) :
X(x), Y(y), Z(z), W(w)
{

}

Quaternion::~Quaternion()
{

}

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);

}