#pragma once

#include <GFK/System/GameTime.hpp>
#include <GFK/Input/TouchEvent.hpp>
#include <GFK/Math/Vector2.hpp>

namespace gfk
{
class GestureRecognizer
{
private:
	enum State
	{
		None,
		OneFingerDown,
		Release,
		OneFingerZoom,
		OneFingerPan,
		ContextMenu,
		TwoFingersDown
	};

	Vector2 oneFingerPanStartPos;

	// OneFingerDown variables
	Vector2 oneFingerStartPos;
	Vector2 panOffset;

	// Release variables
	double currentReleaseTime = 0.0;
	const double maxReleaseTime = 0.3;

	// ContextMenu variables
	double currentContextMenuTime = 0.0;
	const double maxContextMenuTime = 0.4;

	void PrintState();
	std::string StateToString(State state);
	void ChangeState(State newState);

public:
	State state;

	GestureRecognizer();
	~GestureRecognizer();

	void Update(const gfk::GameTime &gameTime);
	void OnTouchEvent(const TouchEvent &event);
};
}
