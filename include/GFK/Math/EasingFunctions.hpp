#pragma once

namespace gfk
{

class EasingFunctions
{

public:
	// t: current time [0, duration]
	// b: beginning value
	// c: change in value
	// d: duration
	static float EaseInBack(float t, float b, float c, float d);
	static float EaseOutBack(float t, float b, float c, float d);
	static float EaseInOutBack(float t, float b, float c, float d);

	static float EaseInBounce(float t, float b, float c, float d);
	static float EaseOutBounce(float t, float b, float c, float d);
	static float EaseInOutBounce(float t, float b, float c, float d);

	static float EaseInCirc(float t, float b, float c, float d);
	static float EaseOutCirc(float t, float b, float c, float d);
	static float EaseInOutCirc(float t, float b, float c, float d);

	static float EaseInCubic(float t, float b, float c, float d);
	static float EaseOutCubic(float t, float b, float c, float d);
	static float EaseInOutCubic(float t, float b, float c, float d);

	static float EaseInElastic(float t, float b, float c, float d);
	static float EaseOutElastic(float t, float b, float c, float d);
	static float EaseInOutElastic(float t, float b, float c, float d);

	static float EaseInExpo(float t, float b, float c, float d);
	static float EaseOutExpo(float t, float b, float c, float d);
	static float EaseInOutExpo(float t, float b, float c, float d);

	static float EaseInLinear(float t, float b, float c, float d);
	static float EaseOutLinear(float t, float b, float c, float d);
	static float EaseInOutLinear(float t, float b, float c, float d);

	static float EaseInQuad(float t, float b, float c, float d);
	static float EaseOutQuad(float t, float b, float c, float d);
	static float EaseInOutQuad(float t, float b, float c, float d);

	static float EaseInQuart(float t, float b, float c, float d);
	static float EaseOutQuart(float t, float b, float c, float d);
	static float EaseInOutQuart(float t, float b, float c, float d);

	static float EaseInQuint(float t, float b, float c, float d);
	static float EaseOutQuint(float t, float b, float c, float d);
	static float EaseInOutQuint(float t, float b, float c, float d);

	static float EaseInSine(float t, float b, float c, float d);
	static float EaseOutSine(float t, float b, float c, float d);
	static float EaseInOutSine(float t, float b, float c, float d);
};

}
