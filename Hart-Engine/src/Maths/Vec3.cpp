#include "HartPch.hpp"
#include "Vec3.hpp"

namespace Hart {
	Vec3::Vec3() {
		initialize(0.0f, 0.0f, 0.0f);
	}

	Vec3::Vec3(float value) {
		initialize(value, value, value);
	}

	Vec3::Vec3(float p_x, float p_y, float p_z) {
		initialize(p_x, p_y, p_z);
	}

	Vec3::Vec3(const Vec2& vec2, float p_z) {
		initialize(vec2.x, vec2.y, p_z);
	}

	const Vec3& Vec3::normalize() {
		*this = GetNormal(*this);
		return *this;
	}

	float Vec3::getMagnitude() {
		return GetMagnitude(*this);
	}

	const Vec3& Vec3::scalarMultiply(float value) {
		*this = ScalarMultiply(*this, value);
		return *this;
	}

	Vec3 Vec3::Add(const Vec3& left, const Vec3& right) {
		return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	Vec3 Vec3::Subtract(const Vec3& left, const Vec3& right) {
		return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	bool Vec3::Equals(const Vec3& left, const Vec3& right) {
		return (left.x == right.x && left.y == right.y && left.z == right.z);
	}

	Vec3 Vec3::ScalarMultiply(const Vec3& vec, float k) {
		return Vec3(vec.x * k, vec.y * k, vec.z * k);
	}

	Vec3 Vec3::Lerp(const Vec3& a, const Vec3& b, float t) {
		return Vec3(
			static_cast<float>(Hart::lerp(a.x, b.x, t)),
			static_cast<float>(Hart::lerp(a.y, b.y, t)),
			static_cast<float>(Hart::lerp(a.z, b.z, t))
		);
	}

	Vec3& Vec3::add(const Vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec3& Vec3::subtract(const Vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	bool Vec3::equals(const Vec3& other) {
		return Vec3::Equals(*this, other);
	}

	Vec3& Vec3::operator+=(const Vec3& other) {
		return this->add(other);
	}

	Vec3& Vec3::operator-=(const Vec3& other) {
		return this->subtract(other);
	}

	bool Vec3::operator==(const Vec3& other) {
		return this->equals(other);
	}

	float Vec3::DotProduct(const Vec3& left, const Vec3& right) {
		return ((left.x * right.x) + (left.y * right.y) + (left.z * right.z));
	}

	Vec3 Vec3::CrossProduct(const Vec3& left, const Vec3& right) {
		return Vec3(
			(left.y * right.z) - (right.y * left.z),
			(left.x * right.z) - (right.x * left.z),
			(left.x * right.y) - (right.x * left.y)
		);
	}

	Vec3 Vec3::GetNormal(const Vec3& vec) {
		float magnitude = GetMagnitude(vec);
		return Vec3(vec.x / magnitude, vec.y / magnitude, vec.z / magnitude);
	}

	float Vec3::GetAngleRBetween(const Vec3& left, const Vec3& right) {
		// angle = acos(a.b / (|a|*|b|) )
		return static_cast<float>(arcCosR(DotProduct(left, right) / (GetMagnitude(left) * GetMagnitude(right))));
	}

	float Vec3::GetAngleDBetween(const Vec3& left, const Vec3& right) {
		return static_cast<float>(radianToDegrees(GetAngleRBetween(left, right)));
	}

	float Vec3::GetMagnitude(const Vec3& vec) {
		// sqrt(x^2+y^2+z^2)
		return static_cast<float>(squareRoot(power(vec.x, 2) + power(vec.y, 2) + power(vec.z, 2)));
	}

	const std::string Vec3::toString() const {
		return std::string("Vec3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
	}

	// private
	void Vec3::initialize(float p_x, float p_y, float p_z) {
		x = p_x;
		y = p_y;
		z = p_z;
	}

	Vec3 operator+(const Vec3& left, const Vec3& right) {
		return Vec3::Add(left, right);
	}

	Vec3 operator-(const Vec3& left, const Vec3& right) {
		return Vec3::Subtract(left, right);
	}

	bool operator==(const Vec3& left, const Vec3& right) {
		return Vec3::Equals(left, right);
	}

	std::ostream& operator<<(std::ostream& stream, Vec3 vec) {
		stream << vec.toString();
		return stream;
	}
}
