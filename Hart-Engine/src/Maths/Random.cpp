#include "HartPch.hpp"
#include "Random.hpp"

namespace Hart {
	namespace Maths {
		Random::Random() {
			const uint32_t seed = m_RandomDevice();
			m_Mt = std::make_unique<std::mt19937>(seed);
		}

		Random::~Random() {

		}

		int Random::getInt32(int a, int b) {
			std::uniform_int_distribution<int32_t> distribution(a, b);
			return distribution(*m_Mt);
		}

		int Random::getInt64(int a, int b) {
			std::uniform_int_distribution<int64_t> distribution(a, b);
			return distribution(*m_Mt);
		}

		float Random::getFloat(float a, float b) {
			std::uniform_real_distribution<float> distribution(a, b);
			return distribution(*m_Mt);
		}

		double Random::getDouble(float a, float b) {
			std::uniform_real_distribution<double> distribution(a, b);
			return distribution(*m_Mt);
		}
	}
}