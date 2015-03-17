#pragma once

#include "objects/GameInput.hpp"
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/System/GameTime.hpp>

using namespace gfk;

namespace jetGame
{

class Jet
{
public:
	Jet();
	Jet(const Vector3 &pos, const Vector3 &initialForward, const Vector3 &initialUp);
	~Jet();

	void Reset();
	void Update(const GameInput &input, const GameTime &gameTime);
	void Update(float throttleAmt, float rollInput, float pitchInput, float yawInput, bool thrusterEnabled, const GameTime &gameTime);
	Vector3 GetPosition() const;
	void SetPosition(const Vector3 &pos);
	Quaternion GetRotation() const;
	void SetRotation(const Quaternion &rot);
	Vector3 GetUp() const;
	Vector3 GetForward() const;
	Vector3 GetRight() const;
	Matrix GetTransform() const;
	float GetEngineRPM() const;
	void SetEngineRPM(float rpm);
protected:
private:
	static const float IDLE_RPM;

	int health;
	Vector3 position;
	float throttle;
	float engineRPM;

	Vector3 initialUp;
	Vector3 initialRight;

	Vector3 forward;
	Vector3 up;
	Vector3 right;

	Quaternion rotQuat;

	void ReOrient();
};

}
