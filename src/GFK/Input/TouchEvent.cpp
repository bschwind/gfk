#include <GFK/Input/TouchEvent.hpp>

namespace gfk
{

TouchEvent::TouchEvent() 
{

}


TouchEvent::~TouchEvent()
{

}

void TouchEvent::PrintTouchEvent(const TouchEvent &event)
{
	Logger::Log("\n");
	Logger::Log("Touch Event Info");

	switch(event.touchType) {
		case Began:
			Logger::Log("State: Began");
			break;
		case Moved:
			Logger::Log("State: Moved");
			break;
		case Ended:
			Logger::Log("State: Ended");
			break;
		case Cancelled:
			Logger::Log("State: Cancelled");
			break;
		case Invalid:
			Logger::Log("State: Invalid");
			break;
	}

	Logger::Logf("Time: %f\n", event.time);
	Logger::Logf("Num Touches: %u\n", static_cast<unsigned int>(event.numTouches));

	for (int i = 0; i < event.numTouches; i++)
	{
		// Matrix world = Matrix::CreateTranslation(Vector3(event.touchPoints[i].pos.X, event.touchPoints[i].pos.Y, 0)) * Matrix::Identity * Matrix::CreateRotationY(MathHelper::ToRadians(90.0f)) * Matrix::CreateScale(20.0f);
		// // primBatch.DrawSphere(Vector3(event.touchPoints[i].pos.X, event.touchPoints[i].pos.Y, 0), 100.0f, 10, 10, Color::Red);
		// primBatch.Begin(PrimitiveType::TriangleList, view, projection, world);
		// primBatch.DrawMesh(mesh);
		// primBatch.End();
	}

	Logger::Log("\n");
}

}
