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

	Vector2 oneFingerPanPos;

	// OneFingerDown variables
	Vector2 oneFingerStartPos;

	void PrintState();

public:
	State state;

	GestureRecognizer();
	~GestureRecognizer();

	void Update(const gfk::GameTime &gameTime);
	void OnTouchEvent(const TouchEvent &event);
};
}
