#include "HartPch.hpp"
#include "Random.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"

namespace Hart {
	Random::Random() : m_MT19937(std::random_device{}()) {
	}

	int32_t Random::getRandomInt32(int32_t begin, int32_t end) {
		std::uniform_int_distribution<int32_t> distribution(begin, end);

		return distribution(m_MT19937);
	}

	int64_t Random::getRandomInt64(int64_t begin, int64_t end) {
		std::uniform_int_distribution<int64_t> distribution(begin, end);
		return distribution(m_MT19937);
	}

	float Random::getRandomFloat(float begin, float end) {
		std::uniform_real_distribution<float> distribution(begin, end);
		return distribution(m_MT19937);
	}

	double Random::getRandomDouble(double begin, double end) {
		std::uniform_real_distribution<double> distribution(begin, end);
		return distribution(m_MT19937);
	}

	Vec2 Random::getRandomVec2(float begin, float end) {
		std::uniform_real_distribution<float> distribution(begin, end);
		return Vec2{
			distribution(m_MT19937),
			distribution(m_MT19937)
		};
	}

	Vec3 Random::getRandomVec3(float begin, float end) {
		std::uniform_real_distribution<float> distribution(begin, end);
		return Vec3{
			distribution(m_MT19937),
			distribution(m_MT19937),
			distribution(m_MT19937)
		};
	}

	Vec4 Random::getRandomVec4(float begin, float end) {
		std::uniform_real_distribution<float> distribution(begin, end);
		return Vec4{
			distribution(m_MT19937),
			distribution(m_MT19937),
			distribution(m_MT19937),
			distribution(m_MT19937)
		};
	}
}
