#include <GFK/VR/VRCamera.hpp>
#include <GFK/System/GameTime.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <iostream>

namespace gfk
{

VRCamera::VRCamera()
{

}

VRCamera::~VRCamera()
{
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();
	std::cout << "Successfully killed VR" << std::endl;
}

void VRCamera::Initialize(std::function<void (gfk::GameTime, float)> renderFunction)
{
	std::cout << "VR Camera initializing!" << std::endl;
	this->renderFunction = renderFunction;
	ovr_Initialize();
	hmd = ovrHmd_Create(0);

	if (hmd)
	{
		std::cout << "We got ourselves a Rift. Here's a bunch of info:" << std::endl << std::endl;
		std::cout << "Product Name: " << hmd->ProductName << std::endl;
		std::cout << "Manufacturer: " << hmd->Manufacturer << std::endl;
		std::cout << "CameraFrustumHFovInRadians: " << hmd->CameraFrustumHFovInRadians << std::endl;
		std::cout << "CameraFrustumVFovInRadians: " << hmd->CameraFrustumVFovInRadians << std::endl;

		std::cout << "CameraFrustumNearZInMeters: " << hmd->CameraFrustumNearZInMeters << std::endl;
		std::cout << "CameraFrustumFarZInMeters: " << hmd->CameraFrustumFarZInMeters << std::endl;
		std::cout << "Resolution.width: " << hmd->Resolution.w << std::endl;
		std::cout << "Resolution.height: " << hmd->Resolution.h << std::endl;
		std::cout << "WindowsPos.x: " << hmd->WindowsPos.x << std::endl;
		std::cout << "WindowsPos.y: " << hmd->WindowsPos.y << std::endl;

		std::cout << "DefaultEyeFov[0].UpTan: " << hmd->DefaultEyeFov[0].UpTan << std::endl;
		std::cout << "DefaultEyeFov[0].DownTan: " << hmd->DefaultEyeFov[0].DownTan << std::endl;
		std::cout << "DefaultEyeFov[0].LeftTan: " << hmd->DefaultEyeFov[0].LeftTan << std::endl;
		std::cout << "DefaultEyeFov[0].RightTan: " << hmd->DefaultEyeFov[0].RightTan << std::endl;

		std::cout << "DefaultEyeFov[1].UpTan: " << hmd->DefaultEyeFov[1].UpTan << std::endl;
		std::cout << "DefaultEyeFov[1].DownTan: " << hmd->DefaultEyeFov[1].DownTan << std::endl;
		std::cout << "DefaultEyeFov[1].LeftTan: " << hmd->DefaultEyeFov[1].LeftTan << std::endl;
		std::cout << "DefaultEyeFov[1].RightTan: " << hmd->DefaultEyeFov[1].RightTan << std::endl;

		std::cout << "EyeRenderOrder[0]: " << hmd->EyeRenderOrder[0] << std::endl;
		std::cout << "EyeRenderOrder[1]: " << hmd->EyeRenderOrder[1] << std::endl;

		std::cout << "DisplayDeviceName: " << hmd->DisplayDeviceName << std::endl;
		std::cout << "DisplayId: " << hmd->DisplayId << std::endl;

		std::cout << std::endl;

		ovrHmd_ConfigureTracking(hmd, ovrTrackingCap_Orientation
			| ovrTrackingCap_MagYawCorrection
			| ovrTrackingCap_Position,
			0);
	}
	else
	{
		std::cout << "Couldn't initialize VRCamera" << std::endl;
	}
}

void VRCamera::Render(const gfk::GameTime &gameTime, float interpolationFactor)
{
	// Render each eye
	for (int i = 0; i < 2; i++)
	{
		if (renderFunction)
		{
			renderFunction(gameTime, interpolationFactor);
		}
	}
}

Vector3 VRCamera::GetPosition()
{
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());

	if (ts.StatusFlags & ovrStatus_PositionTracked)
	{
		ovrPoseStatef pose = ts.HeadPose;
		lastKnownHeadPosition.X = pose.ThePose.Position.x;
		lastKnownHeadPosition.Y = pose.ThePose.Position.y;
		lastKnownHeadPosition.Z = pose.ThePose.Position.z;
	}

	return lastKnownHeadPosition;
}

Quaternion VRCamera::GetRotation()
{
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());

	if (ts.StatusFlags & ovrStatus_OrientationTracked)
	{
		ovrPoseStatef pose = ts.HeadPose;
		lastKnownHeadRotation.X = pose.ThePose.Orientation.x;
		lastKnownHeadRotation.Y = pose.ThePose.Orientation.y;
		lastKnownHeadRotation.Z = pose.ThePose.Orientation.z;
		lastKnownHeadRotation.W = pose.ThePose.Orientation.w;
	}

	return lastKnownHeadRotation;
}

Vector3 VRCamera::GetTrackingCameraPosition()
{
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());

	if (ts.StatusFlags & ovrStatus_CameraPoseTracked)
	{
		ovrPosef pose = ts.CameraPose;
		Vector3 pos;
		pos.X = pose.Position.x;
		pos.Y = pose.Position.y;
		pos.Z = pose.Position.z;

		return pos;
	}

	return Vector3::Zero;
}

Quaternion VRCamera::GetTrackingCameraRotation()
{
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());

	if (ts.StatusFlags & ovrStatus_CameraPoseTracked)
	{
		ovrPosef pose = ts.LeveledCameraPose;
		Quaternion pos;
		pos.X = pose.Orientation.x;
		pos.Y = pose.Orientation.y;
		pos.Z = pose.Orientation.z;
		pos.W = pose.Orientation.w;

		return pos;
	}

	return Quaternion::Identity;
}

void VRCamera::Recenter()
{
	ovrHmd_RecenterPose(hmd);
}

}
