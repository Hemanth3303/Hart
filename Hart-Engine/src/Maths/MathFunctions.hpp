/*
* Basic Maths Functions
*/

#pragma once

#include "HartPch.hpp"
#include "MathConstants.hpp"

namespace Hart {
	namespace Maths {
		// angle unit conversions

		inline double degreeToRadians(double degree) { return (degree * Hart::Maths::PI / 180.0); }
		inline double radianToDegrees(double radian) { return (radian * 180.0 / Hart::Maths::PI); }

		// trignometric functions taking angles as radians

		inline double sinR(double angleInRadians) { return std::sin(angleInRadians); }
		inline double cosR(double angleInRadians) { return std::cos(angleInRadians); }
		inline double tanR(double angleInRadians) { return std::tan(angleInRadians); }
		inline double cotR(double angleInRadians) { return 1.0 / std::tan(angleInRadians); }
		inline double secR(double angleInRadians) { return 1.0 / std::cos(angleInRadians); }
		inline double cosecR(double angleInRadians) { return 1.0 / std::sin(angleInRadians); }

		// inverse trignometric returning angles as radians

		inline double arcSinR(double value) { return std::asin(value); }
		inline double arcCosR(double value) { return std::acos(value); }
		inline double arcTanR(double value) { return std::atan(value); }
		inline double arcTan2R(double valueY, double valueX) { return std::atan2(valueY, valueX); }
		inline double arcSecR(double value) { return std::acos(1 / value); }
		inline double arcCosecR(double value) { return std::asin(1 / value); }

		// trignometric functions taking angles as degrees
		inline double sinD(double angleInDegrees) { return std::sin(degreeToRadians(angleInDegrees)); }
		inline double cosD(double angleInDegrees) { return std::cos(degreeToRadians(angleInDegrees)); }
		inline double tanD(double angleInDegrees) { return std::tan(degreeToRadians(angleInDegrees)); }
		inline double cotD(double angleInDegrees) { return 1.0 / std::tan(degreeToRadians(angleInDegrees)); }
		inline double secD(double angleInDegrees) { return 1.0 / std::cos(degreeToRadians(angleInDegrees)); }
		inline double cosecD(double angleInDegrees) { return 1.0 / std::sin(degreeToRadians(angleInDegrees)); }

		// inverse trignometric returning angles as degrees

		inline double arcSinD(double value) { return radianToDegrees(std::asin(value)); }
		inline double arcCosD(double value) { return radianToDegrees(std::acos(value)); }
		inline double arcTanD(double value) { return radianToDegrees(std::atan(value)); }
		inline double arcTan2D(double valueY, double valueX) { return radianToDegrees(std::atan2(valueY, valueX)); }
		inline double arcSecD(double value) { return radianToDegrees(std::acos(1 / value)); }
		inline double arcCosecD(double value) { return radianToDegrees(std::asin(1 / value)); }

		//other utility functions

		inline double logBaseE(double value) { return std::log(value); }
		inline double logBaseTen(double value) { return std::log10(value); }
		inline double logBaseTwo(double value) { return std::log2(value); }
		inline double power(double value, double exponent) { return std::pow(value, exponent); }
		inline double square(double value) { return power(value, 2); }
		inline double cube(double value) { return power(value, 3); }
		inline double squareRoot(double value) { return std::sqrt(value); }
		inline double cubeRoot(double value) { return power(value, (1.0 / 3.0)); }
		inline double absoluteValue(double value) { return std::abs(value); }
		inline double lerp(double a, double b, double t) { return std::lerp(a, b, t); }
	}
}