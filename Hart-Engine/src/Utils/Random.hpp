#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		// Class with methods for random number generation
		class Random {
		public:
			Random();
			~Random();

			std::int32_t getRandomInt32(std::int32_t begin, std::int32_t end) const;
			std::int64_t getRandomInt64(std::int64_t begin, std::int64_t end) const;

			float getRandomFloat(float begin, float end) const;
			double getRandomDouble(double begin, double end) const;

		private:
			std::unique_ptr<std::mt19937> m_MT19937;
		};
	}
}