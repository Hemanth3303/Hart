#include "HartPch.hpp"
#include "Vec4.hpp"
#include "Vec3.hpp"
#include "Vec2.hpp"
#include "MathFunctions.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	Vec4::Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vec4::Vec4(float value) : x(value), y(value), z(value), w(value) {}
	Vec4::Vec4(float px, float py, float pz, float pw) : x(px), y(py), z(pz), w(pw) {}
	Vec4::Vec4(const Vec2& vec2) : x(vec2.x), y(vec2.y), z(0.0f), w(0.0f) {}
	Vec4::Vec4(const Vec2& vec2, float value) : x(vec2.x), y(vec2.y), z(value), w(value) {}
	Vec4::Vec4(const Vec2& vec2, float pz, float pw) : x(vec2.x), y(vec2.y), z(pz), w(pw) {}
	Vec4::Vec4(const Vec3& vec3) : x(vec3.x), y(vec3.y), z(vec3.z), w(0.0f) {}
	Vec4::Vec4(const Vec3& vec3, float pw) : x(vec3.x), y(vec3.y), z(vec3.z), w(pw) {}

	Vec4 Vec4::Add(const Vec4& lhs, const Vec4& rhs) {
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z,
			lhs.w + rhs.w
		};
	}

	Vec4 Vec4::Subtract(const Vec4& lhs, const Vec4& rhs) {
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z,
			lhs.w - rhs.w
		};
	}

	Vec4 Vec4::ScalarMultiply(const Vec4& vec, float scalar) {
		return {
			vec.x * scalar,
			vec.y * scalar,
			vec.z * scalar,
			vec.w * scalar
		};
	}

	Vec4 Vec4::ComponentWiseMultiplication(const Vec4& lhs, const Vec4& rhs) {
		return {
			lhs.x * rhs.x,
			lhs.y * rhs.y,
			lhs.z * rhs.z,
			lhs.w * rhs.w
		};
	}

	Vec4 Vec4::Lerp(const Vec4& lhs, const Vec4& rhs, float t) {
		return {
			static_cast<float>(Hart::lerp(lhs.x, rhs.x, t)),
			static_cast<float>(Hart::lerp(lhs.y, rhs.y, t)),
			static_cast<float>(Hart::lerp(lhs.z, rhs.z, t)),
			static_cast<float>(Hart::lerp(lhs.w, rhs.w, t))
		};
	}

	float Vec4::DotProduct(const Vec4& lhs, const Vec4& rhs) {
		return (
			(lhs.x * rhs.x) +
			(lhs.y * rhs.y) +
			(lhs.z * rhs.z) +
			(lhs.w * rhs.w));
	}

	float Vec4::GetMagnitude(const Vec4& vec) {
		// sqrt(x^2+y^2+z^2+w^2)
		return static_cast<float>(
			Hart::squareRoot(
				Hart::square(vec.x) + Hart::square(vec.y) +
				Hart::square(vec.z) + Hart::square(vec.w)));
	}

	Vec4 Vec4::GetNormal(const Vec4& vec) {
		float magnitude = GetMagnitude(vec);
		HART_DEBUG_ASSERT(magnitude != 0.0f,
						  "Reason: Can not normalize vector: ",
						  vec,
						  ". Magnitude is 0.");
		if (magnitude == 0.0f) {
			HART_ENGINE_ERROR("Reason: Can not normalize vector: ",
							  vec,
							  ". Magnitude is 0.",
							  ". Returning {0, 0, 0, 0}");
			return { 0.0f, 0.0f, 0.0f, 0.0f };
		}
		return {
			vec.x / magnitude,
			vec.y / magnitude,
			vec.z / magnitude,
			vec.w / magnitude
		};
	}

	float Vec4::GetAngleRBetween(const Vec4& lhs, const Vec4& rhs) {
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

	float Vec4::GetAngleDBetween(const Vec4& lhs, const Vec4& rhs) {
		return static_cast<float>(
			Hart::radianToDegrees(
				GetAngleRBetween(lhs, rhs)));
	}

	std::string Vec4::toString() const {
		return "Vec4(" + std::to_string(x) + ", " + std::to_string(y) +
			   ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
	}

	std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
		os << vec.toString();
		return os;
	}
}
