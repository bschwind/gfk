#include <GFK/Input/GestureRecognizer.hpp>
#include <GFK/Math/MathHelper.hpp>
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

void GestureRecognizer::PrintState()
{
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

std::string GestureRecognizer::StateToString(State state)
{
	switch(state) {
		case None:
			return "None";
			break;
		case OneFingerDown:
			return "OneFingerDown";
			break;
		case Release:
			return "Release";
			break;
		case OneFingerZoom:
			return "OneFingerZoom";
			break;
		case OneFingerPan:
			return "OneFingerPan";
			break;
		case ContextMenu:
			return "ContextMenu";
			break;
		case TwoFingersDown:
			return "TwoFingersDown";
			break;
	}
}

void GestureRecognizer::ChangeState(State newState)
{
	std::string oldStateName = StateToString(state);
	std::string newStateName = StateToString(newState);

	Logger::Logf("%s --> %s", oldStateName.c_str(), newStateName.c_str());

	state = newState;
}

void GestureRecognizer::Update(const gfk::GameTime &gameTime)
{
	// PrintState();

	switch(state) {
		case None:
			break;
		case OneFingerDown:
			currentContextMenuTime += gameTime.ElapsedGameTime;

			// Logger::Logf("Context menu time: %f", currentContextMenuTime);

			if (currentContextMenuTime >= maxContextMenuTime)
			{
				// Logger::Log("Context menu timeout!\n");
				ChangeState(ContextMenu);
				currentContextMenuTime = 0.0;
			}
			break;
		case Release:
			currentReleaseTime += gameTime.ElapsedGameTime;

			if (currentReleaseTime >= maxReleaseTime)
			{
				// Logger::Log("One finger zoom timeout!\n");
				ChangeState(None);
				currentReleaseTime = 0.0;
			}
			break;
		case OneFingerZoom:
			break;
		case OneFingerPan:
			break;
		case ContextMenu:
			// Emit "context menu" event
			ChangeState(OneFingerPan);
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
		{
			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Began)
			{
				ChangeState(OneFingerDown);
				lastOneFingerPos = event.touchPoints[0].pos;
			}
			break;
		}
		case OneFingerDown:
		{
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Cancelled))
			{
				// Touch point went off the screen or somehow it was cancelled
				ChangeState(None);
				currentReleaseTime = 0.0;
			}

			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Moved)
			{
				// 1600 = 40 * 40
				if (Vector2::DistanceSquared(event.touchPoints[0].pos, lastOneFingerPos) > 1600)
				{
					ChangeState(OneFingerPan);
					// Logger::Log("Moved farther than 40 pixels!");
				}
			}

			if (event.numTouches >= 2 && event.touchType == TouchEvent::TouchState::Began)
			{
				ChangeState(TwoFingersDown);
			}

			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Ended)
			{
				// This was a quick tap
				ChangeState(Release);
			}
			break;
		}
		case Release:
		{
			if (event.numTouches == 1 && event.touchType == TouchEvent::TouchState::Began)
			{

				if (Vector2::DistanceSquared(event.touchPoints[0].pos, lastOneFingerPos) < 6400)
				{
					// The user tapped again close to where they tapped before, effectively
					// making this a double tap. Enable one finger zooming
					ChangeState(OneFingerZoom);
				}
				else
				{
					// The user double tapped, but the second tap was far from the first.
					// Treat it as a new single touch down
					ChangeState(OneFingerDown);
					lastOneFingerPos = event.touchPoints[0].pos;
				}
			}
			break;
		}
		case OneFingerZoom:
		{
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				ChangeState(None);
				currentReleaseTime = 0.0;
			}

			if (event.numTouches >= 2 && event.touchType == TouchEvent::TouchState::Began)
			{
				ChangeState(TwoFingersDown);
			}
			break;
		}
		case OneFingerPan:
		{
			if (event.numTouches == 1 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				ChangeState(None);
				currentReleaseTime = 0.0;
			}

			if (event.numTouches >= 2 && event.touchType == TouchEvent::TouchState::Began)
			{
				ChangeState(TwoFingersDown);
			}

			Vector2 offset;
			Vector2::Subtract(event.touchPoints[0].pos, lastOneFingerPos, offset);
			lastOneFingerPos = event.touchPoints[0].pos;
			panAccum += offset;
			break;
		}
		case ContextMenu:
		{
			if (event.touchType == TouchEvent::TouchState::Began)
			{
				ChangeState(TwoFingersDown);
				currentContextMenuTime = 0.0;
			}
			break;
		}
		case TwoFingersDown:
		{
			if (event.numTouches == 2 && (event.touchType == TouchEvent::TouchState::Ended || event.touchType == TouchEvent::TouchState::Cancelled))
			{
				ChangeState(OneFingerPan);
			}

			Vector2 midpoint;
			for (int i = 0; i < event.numTouches; i++)
			{
				midpoint.X += event.touchPoints[i].pos.X;
				midpoint.Y += event.touchPoints[i].pos.Y;
			}

			midpoint /= event.numTouches;

			float avgRotation = 0.0f;
			for (int i = 0; i < event.numTouches; i++)
			{
				Vector2 diff = event.touchPoints[i].pos - midpoint;
				avgRotation += MathHelper::Get2DVecRadians(diff.X, diff.Y);
			}

			avgRotation /= event.numTouches;
			rotateAccum += (avgRotation - lastRotation);
			lastRotation = avgRotation;

			break;
		}
		default:
		{
			Logger::Log("THIS SHOULD NEVER HAPPEN");
			ChangeState(None); // We shouldn't even hit this case
			currentReleaseTime = 0.0;
			break;
		}
	}
}

Vector2 GestureRecognizer::GetPanOffset()
{
	Vector2 temp(panAccum.X, panAccum.Y);
	panAccum.X = 0.0f;
	panAccum.Y = 0.0f;

	return temp;
}

float GestureRecognizer::GetRotationOffset()
{
	float temp = rotateAccum;
	rotateAccum = 0.0f;
	return temp;
}

float GestureRecognizer::GetZoomOffset()
{
	// TODO
	return 1.0f;
}

}
