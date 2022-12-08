/*
* A two component vector
*/

#pragma once

#include "HartPch.hpp"
#include "MathFunctions.hpp"

namespace Hart {
	namespace Maths {
		struct Vec2 {
		public:
			double x, y;
		public:
			// initializes x and y components to 0
			Vec2();
			// initializes x and y components to value
			Vec2(double value);
			Vec2(double p_x, double p_y);
		};
	}
}