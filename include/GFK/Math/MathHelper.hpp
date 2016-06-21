#pragma once

#include <math.h>

namespace gfk
{

class MathHelper
{
private:
	static const float toDegreesFactor;
	static const float toRadiansFactor;
public:
	static const float Pi;
	static const float TwoPi;

	static inline float Barycentric(float v1, float v2, float v3, float amount1, float amount2)
	{
		return v1 + (v2 - v1) * amount1 + (v3 - v1) * amount2;
	}

	static inline float CatmullRom(float v1, float v2, float v3, float v4, float amount)
	{
		// Using formula from http://www.mvps.org/directx/articles/catmull/
		// Internally using doubles not to lose precision
		double amountSquared = amount * amount;
		double amountCubed = amountSquared * amount;
		return (float)(0.5 * (2.0 * v2 +
		(v3 - v1) * amount +
		(2.0 * v1 - 5.0 * v2 + 4.0 * v3 - v4) * amountSquared +
		(3.0 * v2 - v1 - 3.0 * v3 + v4) * amountCubed));

	}

	static inline float Clamp(float value, float min, float max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	static float Hermite(float v1, float tangent1, float v2, float tangent2, float amount);

	static inline float Lerp(float v1, float v2, float amount)
	{
		return v1 + (v2 - v1) * amount;
	}

	static float SmoothStep(float v1, float v2, float amount);

	template <typename T>
	static inline int Sign(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

	template <typename T>
	static inline T ToDegrees(T radians)
	{
		return radians * toDegreesFactor;
	}

	template <typename T>
	static inline T ToRadians(T degrees)
	{
		return degrees * toRadiansFactor;
	}

	// Returns an angle in radians in the range [0, 2PI]
	template <typename T>
	static inline T Get2DVecRadians(T x, T y)
	{
		T angle = atan2(-y, -x);
		angle += Pi;

		return angle;
	}
};

}