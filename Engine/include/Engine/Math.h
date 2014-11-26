
#ifndef EXTRA_MATH_H
#define EXTRA_MATH_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>

#define RAD_TO_DEG 180.0 / M_PI
#define DEG_TO_RAD M_PI / 180.0

struct Math
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

	/*
		Rotate - Vector2f
	*/

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

	static void Rotate(glm::vec2& vec, float deg)
	{
		const float rad = ToRadians(-deg);
		const float sin = std::sinf(rad);
		const float cos = std::cosf(rad);
		const float x2 = vec.x * cos - vec.y * sin;
		const float y2 = vec.x * sin + vec.y * cos;
		vec.x = x2;
		vec.y = y2;
	}

	static void Rotate(float& x, float& y, float deg)
	{
		const float rad = ToRadians(-deg);
		const float sin = std::sinf(rad);
		const float cos = std::cosf(rad);
		const float x2 = x * cos - y * sin;
		const float y2 = x * sin + y * cos;
		x = x2;
		y = y2;
	}
};

#endif // Include guard
