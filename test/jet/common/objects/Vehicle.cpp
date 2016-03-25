#include "objects/Vehicle.hpp"
#include <GFK/Math/MathHelper.hpp>
#include <iostream>
#include <cmath>

namespace jetGame
{

Vehicle::Vehicle() :
Vehicle(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0))
{

}

Vehicle::Vehicle(const Vector3 &pos, const Vector3 &initialForward, const Vector3 &initialUp) :
health(100),
position(pos),
throttle(0.0f),
initialUp(initialUp),
initialRight(Vector3::Cross(initialForward, initialUp)),
forward(initialForward),
up(initialUp),
right(initialRight),
rollVel(0.0f),
pitchVel(0.0f),
yawVel(0.0f),
rotQuat(Quaternion::CreateFromBasisVectors(initialRight, initialUp))
{

}

Vehicle::~Vehicle()
{

}

void Vehicle::Reset()
{
	health = 100;
	position = Vector3::Zero;
	throttle = 0.0f;
	rotQuat = Quaternion::CreateFromBasisVectors(initialRight, initialUp);
}

void Vehicle::Update(const GameInput &input, const GameTime &gameTime)
{

}

void Vehicle::ReOrient()
{
	Vector3::Transform(initialUp, rotQuat, up);
	Vector3::Transform(initialRight, rotQuat, right);
	Vector3::Cross(up, right, forward);
}

Vector3 Vehicle::GetPosition() const
{
	return position;
}

void Vehicle::SetPosition(const Vector3 &pos)
{
	position = pos;
}

Quaternion Vehicle::GetRotation() const
{
	return rotQuat;
}

void Vehicle::SetRotation(const Quaternion &rot)
{
	rotQuat = rot;
}

Vector3 Vehicle::GetUp() const
{
	return up;
}

Vector3 Vehicle::GetForward() const
{
	return forward;
}

Vector3 Vehicle::GetRight() const
{
	return right;
}

Matrix Vehicle::GetTransform() const
{
	return Matrix::CreateTranslation(position) * Matrix::CreateFromQuaternion(rotQuat);
}

float Vehicle::GetRollVel() const
{
	return rollVel;
}

float Vehicle::GetPitchVel() const
{
	return pitchVel;
}


float Vehicle::GetYawVel() const
{
	return yawVel;
}

void Vehicle::SetRollPitchYawVel(float rollVel, float pitchVel, float yawVel)
{
	this->rollVel = rollVel;
	this->pitchVel = pitchVel;
	this->yawVel = yawVel;
}

}
