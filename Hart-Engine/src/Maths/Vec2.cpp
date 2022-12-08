#include "HartPch.hpp"
#include "Vec2.hpp"

namespace Hart {
	namespace Maths {
		Vec2::Vec2() 
			: x(0.0), y(0.0) {
		}

		Vec2::Vec2(double value) 
			: x(value), y(value) {
		}

		Vec2::Vec2(double p_x, double p_y) 
			: x(p_x), y(p_y) {
		}
	}
}
