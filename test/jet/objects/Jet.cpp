#include "objects/Jet.hpp"
#include <iostream>

namespace jetGame
{

const float Jet::IDLE_RPM(1000.0f);

Jet::Jet() :
Jet(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0))
{

}

Jet::Jet(const Vector3 &pos, const Vector3 &initialForward, const Vector3 &initialUp) :
health(100),
position(pos),
throttle(0.0f),
engineRPM(0.0f),
initialUp(initialUp),
initialRight(Vector3::Cross(initialForward, initialUp)),
forward(initialForward),
up(initialUp),
right(initialRight),
rotQuat(Quaternion::CreateFromBasisVectors(initialRight, initialUp))
{

}

Jet::~Jet()
{

}

void Jet::Reset()
{
	health = 100;
	position = Vector3::Zero;
	throttle = 0.0f;
	engineRPM = 0.0f;
	rotQuat = Quaternion::CreateFromBasisVectors(initialRight, initialUp);
}

void Jet::Update(const GameInput &input, const GameTime &gameTime)
{
	float throttle = 0.0f;
	bool thrusterEnabled = false;

	if (input.keyW)
	{
		throttle = 1.0f;
	}
	else if (input.keyS)
	{
		throttle = -1.0f;
	}

	if (input.keyLeftShift)
	{
		thrusterEnabled = true;
	}

	Update(throttle, input.mouseDiffX, input.mouseDiffY, 0.0f, thrusterEnabled, gameTime);
}

void Jet::Update(float throttleAmt, float rollInput, float pitchInput, float yawInput, bool thrusterEnabled, const GameTime &gameTime)
{
	float dt = (float)gameTime.ElapsedGameTime;

	// Update rotational values
	float rollSpeed = 1.0f;
	float pitchSpeed = 1.0f;

	// Update engine speed
	if (engineRPM < IDLE_RPM)
	{
		float startupSpeed = 230.0f;
		engineRPM += startupSpeed * dt;
	}

	float throttleSpeed = thrusterEnabled ? 180.0f : 100.0f;
	engineRPM += throttleAmt * throttleSpeed * dt;

	// Handle Roll
	Quaternion diffQuat = Quaternion::CreateFromAxisAngle(forward, rollInput * rollSpeed * dt);
	rotQuat = diffQuat * rotQuat;

	ReOrient();

	diffQuat = Quaternion::CreateFromAxisAngle(right, pitchInput * pitchSpeed * dt);
	rotQuat = diffQuat * rotQuat;

	rotQuat.Normalize();

	ReOrient();
		
	position += forward * engineRPM * dt * 0.01f;
}

void Jet::ReOrient()
{
	Vector3::Transform(initialUp, rotQuat, up);
	Vector3::Transform(initialRight, rotQuat, right);
	Vector3::Cross(up, right, forward);
}

Vector3 Jet::GetPosition() const
{
	return position;
}

void Jet::SetPosition(const Vector3 &pos)
{
	position = pos;
}

Quaternion Jet::GetRotation() const
{
	return rotQuat;
}

void Jet::SetRotation(const Quaternion &rot)
{
	rotQuat = rot;
}

Vector3 Jet::GetUp() const
{
	return up;
}

Vector3 Jet::GetForward() const
{
	return forward;
}

Vector3 Jet::GetRight() const
{
	return right;
}

Matrix Jet::GetTransform() const
{
	return Matrix::CreateTranslation(position) * Matrix::CreateFromQuaternion(rotQuat);
}

float Jet::GetEngineRPM() const
{
	return engineRPM;
}

void Jet::SetEngineRPM(float rpm)
{
	engineRPM = rpm;
}

}
