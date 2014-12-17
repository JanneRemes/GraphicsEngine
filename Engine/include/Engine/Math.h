
#ifndef EXTRA_MATH_H
#define EXTRA_MATH_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

#define RAD_TO_DEG 180.0 / M_PI
#define DEG_TO_RAD M_PI / 180.0

namespace math
{
	template<class T>
	static inline T ToRadians(T degrees)
	{
		static_assert(std::_Is_numeric<T>::value, "Error: T must be numeric");
		return degrees * static_cast<T>(RAD_TO_DEG);
	}

	template<class T>
	static inline T ToDegrees(T radians)
	{
		static_assert(std::_Is_numeric<T>::value, "Error: T must be numeric");
		return radians * static_cast<T>(DEG_TO_RAD);
	}

	// ---- Rotate - Vector2f

	static glm::vec2 Rotate(const glm::vec2& vec, float deg)
	{
		const float rad = ToRadians(-deg);
		const float sin = std::sinf(rad);
		const float cos = std::cosf(rad);
		return
		{
			vec.x * cos - vec.y * sin,
			vec.x * sin + vec.y * cos
		};
	}

	template<class T>
	static inline T min(T a, T b)
	{
		return a < b ? a : b;
	}

	template<class T>
	static inline T max(T a, T b)
	{
		return a > b ? a : b;
	}
};

#endif // Include guard
