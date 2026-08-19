#include "HartPch.hpp"
#include "Vec3.hpp"
#include "Vec2.hpp"
#include "MathFunctions.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vec3::Vec3(float value) : x(value), y(value), z(value) {}
	Vec3::Vec3(float px, float py, float pz) : x(px), y(py), z(pz) {}
	Vec3::Vec3(const Vec2& vec2) : x(vec2.x), y(vec2.y), z(0.0f) {}
	Vec3::Vec3(const Vec2& vec2, float pz) : x(vec2.x), y(vec2.y), z(pz) {}

	Vec3 Vec3::Add(const Vec3& lhs, const Vec3& rhs) {
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z
		};
	}

	Vec3 Vec3::Subtract(const Vec3& lhs, const Vec3& rhs) {
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z
		};
	}

	Vec3 Vec3::ScalarMultiply(const Vec3& vec, float scalar) {
		return {
			vec.x * scalar,
			vec.y * scalar,
			vec.z * scalar
		};
	}

	Vec3 Vec3::Lerp(const Vec3& lhs, const Vec3& rhs, float t) {
		return {
			static_cast<float>(Hart::lerp(lhs.x, rhs.x, t)),
			static_cast<float>(Hart::lerp(lhs.y, rhs.y, t)),
			static_cast<float>(Hart::lerp(lhs.z, rhs.z, t))
		};
	}

	float Vec3::DotProduct(const Vec3& lhs, const Vec3& rhs) {
		return (
			(lhs.x * rhs.x) +
			(lhs.y * rhs.y) +
			(lhs.z * rhs.z));
	}

	Vec3 Vec3::CrossProduct(const Vec3& lhs, const Vec3& rhs) {
		return {
			(lhs.y * rhs.z) - (lhs.z * rhs.y),
			(lhs.z * rhs.x) - (lhs.x * rhs.z),
			(lhs.x * rhs.y) - (lhs.y * rhs.x)
		};
	}

	float Vec3::GetMagnitude(const Vec3& vec) {
		// sqrt(x^2+y^2+z^2)
		return static_cast<float>(
			Hart::squareRoot(
				Hart::square(vec.x) + Hart::square(vec.y) + Hart::square(vec.z)));
	}

	Vec3 Vec3::GetNormal(const Vec3& vec) {
		float magnitude = GetMagnitude(vec);
		HART_DEBUG_ASSERT(magnitude != 0.0f,
						  "Reason: Can not normalize vector: ",
						  vec,
						  ". Magnitude is 0.");
		if (magnitude == 0.0f) {
			HART_ENGINE_ERROR("Reason: Can not normalize vector: ",
							  vec,
							  ". Magnitude is 0.",
							  ". Returning {0, 0, 0}");
			return { 0.0f, 0.0f, 0.0f };
		}
		return {
			vec.x / magnitude,
			vec.y / magnitude,
			vec.z / magnitude,
		};
	}

	float Vec3::GetAngleRBetween(const Vec3& lhs, const Vec3& rhs) {
		// angle = acos( a.b / (|a|*|b|) )
		float dotProduct = DotProduct(lhs, rhs);
		float lhsMagnitude = GetMagnitude(lhs);
		float rhsMagnitude = GetMagnitude(rhs);
		float denominator = lhsMagnitude * rhsMagnitude;

		HART_DEBUG_ASSERT(denominator != 0.0f,
						  "Reason: Can not normalize vector(s): ",
						  "\tlhs: ", lhs, "\trhs: ", rhs);
		if (denominator == 0.0f) {
			HART_ENGINE_ERROR("Reason: Can not normalize vector(s): ",
							  "\tlhs: ", lhs, "\trhs: ", rhs, "\n\tReturning 0");
			return 0.0f;
		}

		float cosine = dotProduct / denominator;
		// to prevent floating point fuckery (acos domain is [-1.0, 1.0])
		cosine = Hart::clamp(cosine, -1.0f, 1.0f);
		return static_cast<float>(Hart::arcCosR(cosine));
	}

	float Vec3::GetAngleDBetween(const Vec3& lhs, const Vec3& rhs) {
		return static_cast<float>(
			Hart::radianToDegrees(
				GetAngleRBetween(lhs, rhs)));
	}

	std::string Vec3::toString() const {
		return "Vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
	}

	std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
		os << vec.toString();
		return os;
	}
}
