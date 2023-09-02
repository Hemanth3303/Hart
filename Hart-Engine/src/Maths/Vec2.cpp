#include "HartPch.hpp"
#include "Vec2.hpp"

namespace Hart {
	Vec2::Vec2() {
		initialize(0.0f, 0.0f);
	}

	Vec2::Vec2(float value) {
		initialize(value, value);
	}

	Vec2::Vec2(float p_x, float p_y) {
		initialize(p_x, p_y);
	}

	const Vec2& Vec2::normalize() {
		*this = GetNormal(*this);
		return *this;
	}

	float Vec2::getMagnitude() {
		return GetMagnitude(*this);
	}

	const Vec2& Vec2::scalarMultiply(float value) {
		*this = ScalarMultiply(*this, value);
		return *this;
	}

	Vec2 Vec2::Add(const Vec2& left, const Vec2& right) {
		return Vec2(left.x + right.x, left.y + right.y);
	}

	Vec2 Vec2::Subtract(const Vec2& left, const Vec2& right) {
		return Vec2(left.x - right.x, left.y - right.y);
	}

	bool Vec2::Equals(const Vec2& left, const Vec2& right) {
		return (left.x == right.x && left.y == right.y);
	}

	Vec2 Vec2::ScalarMultiply(const Vec2& vec, float k) {
		return Vec2(vec.x * k, vec.y * k);
	}

	Vec2 Vec2::Lerp(const Vec2& a, const Vec2& b, float t) {
		return Vec2(
			static_cast<float>(Hart::lerp(a.x, b.x, t)),
			static_cast<float>(Hart::lerp(a.y, b.y, t))
		);
	}

	Vec2& Vec2::add(const Vec2& other) {
		x += other.x;
		y += other.y;

		return *this;
	}

	Vec2& Vec2::subtract(const Vec2& other) {
		x -= other.x;
		y -= other.y;

		return *this;
	}

	bool Vec2::equals(const Vec2& other) {
		return Vec2::Equals(*this, other);
	}

	Vec2& Vec2::operator+=(const Vec2& other) {
		return this->add(other);
	}

	Vec2& Vec2::operator-=(const Vec2& other) {
		return this->subtract(other);
	}

	bool Vec2::operator==(const Vec2& other) {
		return this->equals(other);
	}

	float Vec2::DotProduct(const Vec2& left, const Vec2& right) {
		return ((left.x * right.x) + (left.y * right.y));
	}

	Vec2 Vec2::GetNormal(const Vec2& vec) {
		float magnitude = GetMagnitude(vec);
		return Vec2(vec.x / magnitude, vec.y / magnitude);
	}

	float Vec2::GetAngleRBetween(const Vec2& left, const Vec2& right) {
		// angle = acos(a.b / (|a|*|b|) )
		return static_cast<float>(arcCosR(DotProduct(left, right) / (GetMagnitude(left) * GetMagnitude(right))));
	}

	float Vec2::GetAngleDBetween(const Vec2& left, const Vec2& right) {
		return static_cast<float>(radianToDegrees(GetAngleRBetween(left, right)));
	}

	float Vec2::GetMagnitude(const Vec2& vec) {
		// sqrt(x^2+y^2)
		return static_cast<float>(squareRoot(power(vec.x, 2) + power(vec.y, 2)));
	}

	const std::string Vec2::toString() const {
		return std::string("Vec2(" + std::to_string(x) + ", " + std::to_string(y) + ")");
	}

	// private
	void Vec2::initialize(float p_x, float p_y) {
		x = p_x;
		y = p_y;
	}

	Vec2 operator+(const Vec2& left, const Vec2& right) {
		return Vec2::Add(left, right);
	}

	Vec2 operator-(const Vec2& left, const Vec2& right) {
		return Vec2::Subtract(left, right);
	}

	bool operator==(const Vec2& left, const Vec2& right) {
		return Vec2::Equals(left, right);
	}

	std::ostream& operator<<(std::ostream& stream, Vec2 vec) {
		stream << vec.toString();
		return stream;
	}
}
