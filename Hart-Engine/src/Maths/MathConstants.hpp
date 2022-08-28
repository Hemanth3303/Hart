/*
* Commonly used maths constants
*/

#pragma once
#include "HartPch.hpp"

namespace Hart {
	namespace Maths {
		//Value of PI
		const double PI = std::atan2(0, -1);
		//Euler's number e, lt[x->+infinity]{(1+1/x)^x}
		const double E = std::exp(1);
	}
}