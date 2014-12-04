#pragma once

#include <functional>
#include <OVR.h>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>

namespace gfk
{

class GameTime;

class VRCamera
{
public:
	VRCamera();
	~VRCamera();
	void Initialize(std::function<void (gfk::GameTime, float)> renderFunction);
	void Render(const gfk::GameTime &gameTime, float interpolationFactor);
	Vector3 GetPosition();
	Quaternion GetRotation();
	Vector3 GetTrackingCameraPosition();
	Quaternion GetTrackingCameraRotation();
	void Recenter();
protected:
private:
	ovrHmd hmd;
	Vector3 lastKnownHeadPosition;
	Quaternion lastKnownHeadRotation;

	// We will call this function for each eye
	std::function<void (gfk::GameTime, float)> renderFunction;
};

}
