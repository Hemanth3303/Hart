#include "HartPch.hpp"
#include "Random.hpp"

namespace Hart {
	namespace Utils {
		Random::Random() {
			std::random_device randomDevice;
			m_MT19937 = std::make_unique<std::mt19937>(randomDevice());
		}

		Random::~Random() {

		}

		int32_t Random::getRandomInt32(int32_t begin, int32_t end) {
			std::uniform_int_distribution<int32_t> distribution(begin, end);

			return distribution(*(m_MT19937.get()));
		}

		int64_t Random::getRandomInt64(int64_t begin, int64_t end) {
			std::uniform_int_distribution<int64_t> distribution(begin, end);
			return distribution(*(m_MT19937.get()));
		}

		float Random::getRandomFloat(float begin, float end) {
			std::uniform_real_distribution<double> distribution(begin, end);
			return static_cast<float>(distribution(*(m_MT19937.get())));
		}

		double Random::getRandomDouble(double begin, double end) {
			std::uniform_real_distribution<double> distribution(begin, end);
			return distribution(*(m_MT19937.get()));
		}
	}
}