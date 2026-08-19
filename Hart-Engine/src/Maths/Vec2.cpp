#include "HartPch.hpp"
#include "Vec2.hpp"
#include "MathFunctions.hpp"

namespace Hart {
	Vec2::Vec2() : x(0), y(0) {}
	Vec2::Vec2(float value) : x(value), y(value) {}
	Vec2::Vec2(float px, float py) : x(px), y(py) {}

	Vec2 Vec2::Add(const Vec2& lhs, const Vec2& rhs) {
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y
		};
	}

	Vec2 Vec2::Subtract(const Vec2& lhs, const Vec2& rhs) {
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y
		};
	}

	Vec2 Vec2::ScalarMultiply(const Vec2& vec, float scalar) {
		return {
			vec.x * scalar,
			vec.y * scalar
		};
	}

	Vec2 Vec2::Lerp(const Vec2& lhs, const Vec2& rhs, float t) {
		return {
			static_cast<float>(Hart::lerp(lhs.x, rhs.x, t)),
			static_cast<float>(Hart::lerp(lhs.y, rhs.y, t)),
		};
	}

	float Vec2::DotProduct(const Vec2& lhs, const Vec2& rhs) {
		return ((lhs.x * rhs.x) + (lhs.y * rhs.y));
	}

	float Vec2::GetMagnitude(const Vec2& vec) {
		// sqrt(x^2+y^2)
		return static_cast<float>(
			Hart::squareRoot(
				Hart::square(vec.x) + Hart::square(vec.y)));
	}

	Vec2 Vec2::GetNormal(const Vec2& vec) {
		float magnitude = GetMagnitude(vec);
		return {
			vec.x / magnitude,
			vec.y / magnitude
		};
	}

	float Vec2::GetAngleRBetween(const Vec2& lhs, const Vec2& rhs) {
		// angle = acos( a.b / (|a|*|b|) )
		float dotProduct = DotProduct(lhs, rhs);
		float lhsMagnitude = GetMagnitude(lhs);
		float rhsMagnitude = GetMagnitude(rhs);

		return static_cast<float>(
			Hart::arcCosR(dotProduct / (lhsMagnitude * rhsMagnitude)));
	}

	float Vec2::GetAngleDBetween(const Vec2& lhs, const Vec2& rhs) {
		return static_cast<float>(
			Hart::radianToDegrees(
				GetAngleRBetween(lhs, rhs)));
	}

	std::string Vec2::toString() const {
		return "Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}

	std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
		os << vec.toString();
		return os;
	}
}
