#pragma once

#include <GFK/Math/Vector2.hpp>
#include <GFK/System/Logger.hpp>
#include <stdint.h>

namespace gfk
{
class TouchEvent
{
public:
	static const unsigned char MAX_TOUCHES = 10;

	static void PrintTouchEvent(const TouchEvent &event);

	enum TouchState
	{
		Began,
		Moved,
		Ended,
		Cancelled,
		Invalid
	};

	struct TouchPoint {
		uintptr_t id = 0;
		Vector2 pos;
		Vector2 lastPos;
		bool isChanged = false;
	};

	TouchState touchType;
	double time;
	unsigned char numTouches;
	TouchPoint touchPoints[MAX_TOUCHES];

	TouchEvent();
	~TouchEvent();
};
}
