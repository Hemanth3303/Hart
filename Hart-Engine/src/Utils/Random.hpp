#pragma once

#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"

#include <random>
#include <cstdint>

namespace Hart {
	// Class with methods for random number generation
	class Random {
	public:
		Random();
		~Random() = default;

		int32_t getRandomInt32(int32_t begin, int32_t end);
		int64_t getRandomInt64(int64_t begin, int64_t end);

		float getRandomFloat(float begin, float end);
		double getRandomDouble(double begin, double end);

		Vec2 getRandomVec2(float begin, float end);
		Vec3 getRandomVec3(float begin, float end);
		Vec4 getRandomVec4(float begin, float end);

	private:
		std::mt19937 m_MT19937;
	};
}
