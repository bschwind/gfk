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
	PrintState();

	switch(state) {
		case None:
			break;
		case OneFingerDown:
			break;
		case Release:
			currentReleaseTime += gameTime.ElapsedGameTime;

			if (currentReleaseTime >= maxReleaseTime)
			{
				Logger::Log("Timeout!\n");
				state = None;
				currentReleaseTime = 0.0;
			}
			break;
		case OneFingerZoom:
			break;
		case OneFingerPan:
			break;
		case ContextMenu:
			break;
		case TwoFingersDown:
			break;
	}
}

void GestureRecognizer::OnTouchEvent(const TouchEvent &event)
{
	// TouchEvent::PrintTouchEvent(event);

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
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Cancelled))
			{
				// Touch point went off the screen or somehow it was cancelled
				Logger::Log("Going to None state!\n");
				state = None;
				currentReleaseTime = 0.0;
			}

			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Moved)
			{
				// 1600 = 40 * 40
				if (Vector2::DistanceSquared(event.touchPoints[0].pos, oneFingerStartPos) > 1600)
				{
					state = OneFingerPan;
					oneFingerPanStartPos = event.touchPoints[0].pos;
					Logger::Log("Moved farther than 40 pixels!");
				}
			}

			if (event.numTouches >= 2 && event.touchType == TouchEvent::TouchState::Began)
			{
				state = TwoFingersDown;
			}

			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Ended)
			{
				// This was a quick tap
				Logger::Log("Going to Release state!\n");
				state = Release;
			}
			break;
		case Release:
			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Began)
			{
				if (Vector2::DistanceSquared(event.touchPoints[0].pos, oneFingerStartPos) < 1600)
				{
					// The user tapped again close to where they tapped before, effectively
					// making this a double tap. Enable one finger zooming
					Logger::Log("Going to one finger zoom!\n");
					state = OneFingerZoom;
				}
				else
				{
					// The user double tapped, but the second tap was far from the first.
					// Treat it as a new single touch down
					Logger::Log("Going to one finger down!\n");
					state = OneFingerDown;
					oneFingerStartPos = event.touchPoints[0].pos;
				}
			}

			Logger::Log("In release state!\n");
			break;
		case OneFingerZoom:
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				state = None;
				currentReleaseTime = 0.0;
			}

			if (event.numTouches >= 2 && event.touchType == TouchEvent::TouchState::Began)
			{
				state = TwoFingersDown;
			}
			break;
		case OneFingerPan:
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				state = None;
				currentReleaseTime = 0.0;
			}

			if (event.numTouches >= 2 && event.touchType == TouchEvent::TouchState::Began)
			{
				state = TwoFingersDown;
			}

			Logger::Logf("Distance from start touch: %f\n", Vector2::Distance(event.touchPoints[0].pos, oneFingerStartPos));
			Vector2::Subtract(event.touchPoints[0].pos, oneFingerStartPos, panOffset);
			Logger::Logf("Offset: (%f,%f)\n", panOffset.X, panOffset.Y);

			break;
		case ContextMenu:
			break;
		case TwoFingersDown:
			if (event.numTouches == 2 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				state = OneFingerPan;
			}
			break;
		default:
			Logger::Log("THIS SHOULD NEVER HAPPEN");
			state = None; // We shouldn't even hit this case
			currentReleaseTime = 0.0;
			break;
	}
}

}
