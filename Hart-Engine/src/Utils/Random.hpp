/*
* Class with methods for random number generation
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class Random {
		public:
			Random();
			~Random();

			int32_t getRandomInt32(int32_t begin, int32_t end);
			int64_t getRandomInt64(int64_t begin, int64_t end);

			float getRandomFloat(float begin, float end);
			double getRandomDouble(double begin, double end);
		private:
			std::unique_ptr<std::mt19937> m_MT19937;
		};
	}
}