#include "HartPch.hpp"
#include "Random.hpp"

#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"

namespace Hart {
	namespace Utils {
		Random::Random() {
			std::random_device randomDevice;
			m_MT19937 = std::make_unique<std::mt19937>(randomDevice());
		}

		Random::~Random() {

		}

		std::int32_t Random::getRandomInt32(std::int32_t begin, std::int32_t end) const {
			std::uniform_int_distribution<std::int32_t> distribution(begin, end);

			return distribution(*(m_MT19937.get()));
		}

		std::int64_t Random::getRandomInt64(std::int64_t begin, std::int64_t end) const {
			std::uniform_int_distribution<std::int64_t> distribution(begin, end);
			return distribution(*(m_MT19937.get()));
		}

		float Random::getRandomFloat(float begin, float end) const {
			std::uniform_real_distribution<double> distribution(begin, end);
			return static_cast<float>(distribution(*(m_MT19937.get())));
		}

		double Random::getRandomDouble(double begin, double end) const {
			std::uniform_real_distribution<double> distribution(begin, end);
			return distribution(*(m_MT19937.get()));
		}
        Maths::Vec2 Random::getRandomVec2(float begin, float end) const {
			std::uniform_real_distribution<> distribution(begin, end);
            return Maths::Vec2(
				static_cast<float>(distribution(*(m_MT19937.get()))),
				static_cast<float>(distribution(*(m_MT19937.get())))
			);
        }
        Maths::Vec3 Random::getRandomVec3(float begin, float end) const {
			std::uniform_real_distribution<> distribution(begin, end);
			return Maths::Vec3(
				static_cast<float>(distribution(*(m_MT19937.get()))),
				static_cast<float>(distribution(*(m_MT19937.get()))),
				static_cast<float>(distribution(*(m_MT19937.get())))
			);
        }
        Maths::Vec4 Random::getRandomVec4(float begin, float end) const {
			std::uniform_real_distribution<> distribution(begin, end);
			return Maths::Vec4(
				static_cast<float>(distribution(*(m_MT19937.get()))),
				static_cast<float>(distribution(*(m_MT19937.get()))),
				static_cast<float>(distribution(*(m_MT19937.get()))),
				static_cast<float>(distribution(*(m_MT19937.get())))
			);
        }
	}
}