#include "objects/Jet.hpp"
#include <GFK/Math/MathHelper.hpp>
#include <iostream>
#include <cmath>

namespace jetGame
{

const float Jet::IDLE_RPM(1000.0f);

Jet::Jet() :
Vehicle(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0)),
engineRPM(0.0f)
{

}

Jet::~Jet()
{

}

void Jet::Reset()
{
	Vehicle::Reset();
	engineRPM = 0.0f;
}

float Jet::GetEngineRPM() const
{
	return engineRPM;
}

void Jet::SetEngineRPM(float rpm)
{
	engineRPM = rpm;
}

void Jet::Update(const GameInput &input, const GameTime &gameTime)
{
	float throttle = 0.0f;
	float yawInput = 0.0f;
	bool thrusterEnabled = false;

	if (input.keyW)
	{
		throttle = 1.0f;
	}
	else if (input.keyS)
	{
		throttle = -1.0f;
	}

	if (input.keyA)
	{
		yawInput = 1.0f;
	}
	else if (input.keyD)
	{
		yawInput = -1.0f;
	}

	if (input.keyLeftShift)
	{
		thrusterEnabled = true;
	}

	Update(throttle, input.mouseDiffX, input.mouseDiffY, yawInput, thrusterEnabled, gameTime);
}

void Jet::Update(float throttleAmt, float rollInput, float pitchInput, float yawInput, bool thrusterEnabled, const GameTime &gameTime)
{
	float dt = (float)gameTime.ElapsedGameTime;

	// Update rotational values
	float rollSpeed = 0.015f;
	float pitchSpeed = 0.015f;
	float yawSpeed = 0.015f;

	// Update engine speed
	if (engineRPM < IDLE_RPM)
	{
		float startupSpeed = 230.0f;
		engineRPM += startupSpeed * dt;
	}

	float throttleSpeed = thrusterEnabled ? 180.0f : 100.0f;
	engineRPM += throttleAmt * throttleSpeed * dt;

	// Handle Yaw
	yawVel += yawInput * yawSpeed * dt;
	yawVel *= 0.9f;
	if (fabs(yawVel) <= 0.000005f) {
		yawVel = 0.0f;
	}
	Quaternion diffQuat = Quaternion::CreateFromAxisAngle(up, yawVel);
	rotQuat = diffQuat * rotQuat;

	ReOrient();

	// Handle Roll
	rollVel += rollInput * rollSpeed * dt;
	rollVel *= 0.9f;
	rollVel = MathHelper::Clamp(rollVel, -0.09f, 0.09f);
	if (fabs(rollVel) <= 0.000005f) {
		rollVel = 0.0f;
	}
	diffQuat = Quaternion::CreateFromAxisAngle(forward, rollVel);
	rotQuat = diffQuat * rotQuat;

	ReOrient();

	// Handle Pitch
	pitchVel += pitchInput * pitchSpeed * dt;
	pitchVel *= 0.9f;
	pitchVel = MathHelper::Clamp(pitchVel, -0.05f, 0.05f);
	if (fabs(pitchVel) <= 0.000005f) {
		pitchVel = 0.0f;
	}
	diffQuat = Quaternion::CreateFromAxisAngle(right, pitchVel);
	rotQuat = diffQuat * rotQuat;

	// Prevent numerical drift
	rotQuat.Normalize();

	ReOrient();
		
	position += forward * engineRPM * dt * 0.01f;
}

}
