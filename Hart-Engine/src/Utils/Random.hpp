#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		// Class with methods for random number generation
		class Random {
		public:
			Random();
			~Random();

			int32_t getRandomInt32(int32_t begin, int32_t end) const;
			int64_t getRandomInt64(int64_t begin, int64_t end) const;

			float getRandomFloat(float begin, float end) const;
			double getRandomDouble(double begin, double end) const;
		private:
			std::unique_ptr<std::mt19937> m_MT19937;
		};
	}
}