#pragma once

namespace gfk
{

class MathHelper
{
public:
	static inline float Barycentric(float v1, float v2, float v3, float amount1, float amount2)
	{
		return v1 + (v2 - v1) * amount1 + (v3 - v1) * amount2;
	}

	static inline float CatmullRom(float v1, float v2, float v3, float v4, float amount)
	{
		// Using formula from http://www.mvps.org/directx/articles/catmull/
		// Internally using doubles not to lose precission
		double amountSquared = amount * amount;
		double amountCubed = amountSquared * amount;
		return (float)(0.5 * (2.0 * v2 +
		(v3 - v1) * amount +
		(2.0 * v1 - 5.0 * v2 + 4.0 * v3 - v4) * amountSquared +
		(3.0 * v2 - v1 - 3.0 * v3 + v4) * amountCubed));

	}

	static inline float Clamp(const float value, const float min, const float max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	static inline void Clamp(float &value, const float min, const float max)
	{
		value = (value < min) ? min : (value > max ? max : value);
	}

	static float Hermite(float v1, float tangent1, float v2, float tangent2, float amount);

	static inline float Lerp(float v1, float v2, float amount)
	{
		return v1 + (v2 - v1) * amount;
	}
};

}