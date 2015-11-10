#pragma once

#include <GFK/Math/Vector2.hpp>
#include <stdint.h>

namespace gfk
{
class TouchEvent
{
public:
	static const unsigned char MAX_TOUCHES = 10;

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
