/*
* Commonly used maths functions
* Note: Trignometric functions ending in R takes in angle as radians, while those ending with D take in angle as degrees
* Note: Inverse Trignometric functions ending in R give angle as radians, while those ending with D give angle as degrees
*/

#pragma once
#include "MathConstants.hpp"

#include <cmath>
#include <algorithm>

namespace Hart {
	namespace Maths {
		inline auto degreeToRadian(const auto& degree) { return degree * (PI / 180); }

		inline auto radiansToDegree(const auto& radians) { return radians * (180 / PI); }

		/*
		* trignometric function
		*/
		inline auto sinR(const auto& radianAngle) { return std::sin(radianAngle); }
		inline auto cosR(const auto& radianAngle) { return std::cos(radianAngle); }
		inline auto tanR(const auto& radianAngle) { return std::tan(radianAngle); }
		inline auto cotR(const auto& radianAngle) { return (1 / std::tan(radianAngle)); }
		inline auto secR(const auto& radianAngle) { return (1 / std::cos(radianAngle)); }
		inline auto cosecR(const auto& radianAngle) { return (1 / std::sin(radianAngle)); }

		inline auto sinD(const auto& degreeAngle) { return std::sin(degreeToRadian(degreeAngle)); }
		inline auto cosD(const auto& degreeAngle) { return std::cos(degreeToRadian(degreeAngle)); }
		inline auto tanD(const auto& degreeAngle) { return std::tan(degreeToRadian(degreeAngle)); }
		inline auto cotD(const auto& degreeAngle) { return 1 / std::tan(degreeToRadian(degreeAngle)); }
		inline auto secD(const auto& degreeAngle) { return 1 / std::cos(degreeToRadian(degreeAngle)); }
		inline auto cosecD(const auto& degreeAngle) { return 1 / std::sin(degreeToRadian(degreeAngle)); }

		/*
		* inverse trignometric function
		*/
		inline auto aSinR(const auto& value) { return std::asin(value); }
		inline auto aCosR(const auto& value) { return std::acos(value); }
		inline auto aTanR(const auto& value) { return std::atan(value); }
		inline auto aTan2R(const auto& y, const auto& x) { return std::atan2(y, x); }

		inline auto aSinD(const auto& value) { return radiansToDegree(std::asin(value)); }
		inline auto aCosD(const auto& value) { return radiansToDegree(std::acos(value)); }
		inline auto aTanD(const auto& value) { return radiansToDegree(std::atan(value)); }
		inline auto aTan2D(const auto& y, const auto& x) { return radiansToDegree(std::atan2(y, x)); }

		/*
		* other functions
		*/

		//returns e raised to value, where e is the Euler's number
		inline auto exponential(const auto& value) { return std::exp(value); }
		inline auto logBaseE(const auto& value) { return std::log(value); }
		inline auto logBaseTen(const auto& value) { return std::log10(value); }
		inline auto logBaseTwo(const auto& value) { return std::log2(value); }

		// Computes the linear interpolation between a and b, if the parameter t is inside [0, 1], otherwise calculates the linear extrapolation, i.e. the result of a+t(b-a) with accounting for floating-point calculation imprecision.
		inline auto lerp(const auto& a, const auto& b, const auto& t) { return std::lerp(a, b, t); }
		// If value compares less than low, returns low; otherwise if high compares less than value, returns high. Otherwise returns value. Uses operator < to compare the values.
		inline auto clamp(const auto& value, const auto& low, const auto& high) { return std::clamp(value, low, high); }

	}
}