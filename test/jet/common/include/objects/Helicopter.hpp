#pragma once

#include "objects/Vehicle.hpp"
#include "objects/GameInput.hpp"
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/System/GameTime.hpp>

using namespace gfk;

namespace jetGame
{

class Helicopter : public Vehicle
{
public:
	Helicopter();
	Helicopter(const Vector3 &pos, const Vector3 &initialForward, const Vector3 &initialUp);
	~Helicopter();

	void Reset() override;
	void Update(const GameInput &input, const GameTime &gameTime) override;
	float GetEngineRPM() const;
	void SetEngineRPM(float rpm);
protected:
private:
	static const float IDLE_RPM;

	float engineRPM;

	void Update(float throttleAmt, float rollInput, float pitchInput, float yawInput, bool thrusterEnabled, const GameTime &gameTime);
};

}
