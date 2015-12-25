#include <GFK/Input/GestureRecognizer.hpp>
#include <GFK/System/Logger.hpp>

namespace gfk
{

GestureRecognizer::GestureRecognizer() :
state(None)
{

}


GestureRecognizer::~GestureRecognizer()
{

}

void GestureRecognizer::PrintState() {
	switch(state) {
		case None:
			Logger::Log("GestureRecognizer State: None");
			break;
		case OneFingerDown:
			Logger::Log("GestureRecognizer State: OneFingerDown");
			break;
		case Release:
			Logger::Log("GestureRecognizer State: Release");
			break;
		case OneFingerZoom:
			Logger::Log("GestureRecognizer State: OneFingerZoom");
			break;
		case OneFingerPan:
			Logger::Log("GestureRecognizer State: OneFingerPan");
			break;
		case ContextMenu:
			Logger::Log("GestureRecognizer State: ContextMenu");
			break;
		case TwoFingersDown:
			Logger::Log("GestureRecognizer State: TwoFingersDown");
			break;
	}
}

void GestureRecognizer::Update(const gfk::GameTime &gameTime)
{
	// PrintState();
}

void GestureRecognizer::OnTouchEvent(const TouchEvent &event)
{
	TouchEvent::PrintTouchEvent(event);

	switch(state)
	{
		case None:
			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Began)
			{
				state = OneFingerDown;
				oneFingerStartPos = event.touchPoints[0].pos;
			}
			break;
		case OneFingerDown:
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				state = None;
			}

			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Moved)
			{
				// 1600 = 40 * 40
				if (Vector2::DistanceSquared(event.touchPoints[0].pos, oneFingerStartPos) > 1600)
				{
					state = OneFingerPan;
					oneFingerPanPos = event.touchPoints[0].pos;
					Logger::Log("Moved farther than 20 pixels!");
				}
			}
			break;
		case Release:
			break;
		case OneFingerZoom:
			break;
		case OneFingerPan:
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				state = None;
			}

			Logger::Logf("Distance from start touch: %f\n", Vector2::Distance(event.touchPoints[0].pos, oneFingerStartPos));

			break;
		case ContextMenu:
			break;
		case TwoFingersDown:
			break;
		default:
			Logger::Log("THIS SHOULD NEVER HAPPEN");
			state = None; // We shouldn't even hit this case
			break;
	}
}

}
