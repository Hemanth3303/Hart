#pragma once

#include "HartPch.hpp"

#include <random>

namespace Hart {
	namespace Maths {
		class Random {
		public:
			// Create an instance of the random number generator class
			Random();
			~Random();

			// Returns a 32 bit int between a and b
			int getInt32(int a, int b);
			// Returns a 64 bit int between a and b
			int getInt64(int a, int b);
			// Returns a float between a and b
			float getFloat(float a, float b);
			// Returns a double between a and b
			double getDouble(float a, float b);
		private:
			std::random_device m_RandomDevice;
			std::unique_ptr<std::mt19937> m_Mt;
		};
	}
}