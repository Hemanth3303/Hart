/*
* Commonly used maths functions
* Note: Trignometric functions ending in R takes in angle as radians, while those ending with D take in angle as degrees
*/

#pragma once
#include "MathConstants.hpp"

#include <cmath>

namespace Hart {
	namespace Maths {
		inline auto DegreeToRadian(const auto& degree) { return degree * (PI / 180); }

		inline auto RadiansToDegree(const auto& radians) { return radians * (180 / PI); }

		inline auto SinR(const auto& radianAngle) { return std::sin(radianAngle); }
		inline auto CosR(const auto& radianAngle) { return std::cos(radianAngle); }
		inline auto TanR(const auto& radianAngle) { return std::tan(radianAngle); }
		inline auto CotR(const auto& radianAngle) { return (1 / std::tan(radianAngle)); }
		inline auto SecR(const auto& radianAngle) { return (1 / std::cos(radianAngle)); }
		inline auto CosecR(const auto& radianAngle) { return (1 / std::sin(radianAngle)); }

		inline auto SinD(const auto& degreeAngle) { return std::sin(DegreeToRadian(degreeAngle)); }
		inline auto CosD(const auto& degreeAngle) { return std::cos(DegreeToRadian(degreeAngle)); }
		inline auto TanD(const auto& degreeAngle) { return std::tan(DegreeToRadian(degreeAngle)); }
		inline auto CotD(const auto& degreeAngle) { return 1 / std::tan(DegreeToRadian(degreeAngle)); }
		inline auto SecD(const auto& degreeAngle) { return 1 / std::cos(DegreeToRadian(degreeAngle)); }
		inline auto CosecD(const auto& degreeAngle) { return 1 / std::sin(DegreeToRadian(degreeAngle)); }

	}
}