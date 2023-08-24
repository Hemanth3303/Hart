#pragma once

#include "HartPch.hpp"

namespace Hart {
	// Class with methods for random number generation
	class Random {
	public:
		Random();
		~Random();

		std::int32_t getRandomInt32(std::int32_t begin, std::int32_t end) const;
		std::int64_t getRandomInt64(std::int64_t begin, std::int64_t end) const;

		float getRandomFloat(float begin, float end) const;
		double getRandomDouble(double begin, double end) const;

		Vec2 getRandomVec2(float begin, float end) const;
		Vec3 getRandomVec3(float begin, float end) const;
		Vec4 getRandomVec4(float begin, float end) const;

	private:
		std::unique_ptr<std::mt19937> m_MT19937;
	};
}