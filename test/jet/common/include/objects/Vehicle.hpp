#pragma once

#include "objects/GameInput.hpp"
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/System/GameTime.hpp>

using namespace gfk;

namespace jetGame
{

class Vehicle
{
public:
	Vehicle();
	Vehicle(const Vector3 &pos, const Vector3 &initialForward, const Vector3 &initialUp);
	~Vehicle();

	virtual void Reset();
	virtual void Update(const GameInput &input, const GameTime &gameTime);
	Vector3 GetPosition() const;
	void SetPosition(const Vector3 &pos);
	Quaternion GetRotation() const;
	void SetRotation(const Quaternion &rot);
	Vector3 GetUp() const;
	Vector3 GetForward() const;
	Vector3 GetRight() const;
	Matrix GetTransform() const;
	float GetRollVel() const;
	float GetPitchVel() const;
	float GetYawVel() const;
	void SetRollPitchYawVel(float rollVel, float pitchVel, float yawVel);
protected:
	int health;
	Vector3 position;
	float throttle;
	Vector3 initialUp;
	Vector3 initialRight;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
	float rollVel;
	float pitchVel;
	float yawVel;
	Quaternion rotQuat;
	void ReOrient();
private:
};

}
