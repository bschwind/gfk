#include <GFK/MathHelper.hpp>

namespace gfk
{
	float MathHelper::Hermite(float v1, float tangent1, float v2, float tangent2, float amount)
	{
		// All transformed to double not to lose precission
		// Otherwise, for high numbers of param:amount the result is NaN instead of Infinity
		double d1 = v1, d2 = v2, t1 = tangent1, t2 = tangent2, s = amount, result;
		double sSquared = s * s;
		double sCubed = s * sSquared;

		if (amount == 0.0f)
		{
			result = v1;
		}
		else if (amount == 1.0f)
		{
			result = v2;
		}
		else
		{
			result = (2 * d1 - 2 * d2 + t2 + t1) * sCubed +
			(3 * d2 - 3 * d1 - 2 * t1 - t2) * sSquared +
			t1 * s + d1;
		}

		return (float)result;
	}

	float MathHelper::SmoothStep(float v1, float v2, float amount)
	{
		float result = MathHelper::Clamp(amount, 0.0f, 1.0f);
		result = MathHelper::Hermite(v1, 0.0f, v2, 0.0f, result);
		return result;
	}
}