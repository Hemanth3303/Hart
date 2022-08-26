#include "Core/HartPch.hpp"
#include "Vec2.hpp"

namespace Hart {
	namespace Maths {

		Vec2::Vec2() {
			x = 0.0f;
			y = 0.0f;
		}

		Vec2::Vec2(const float& x, const float& y) {
			this->x = x;
			this->y = y;
		}

		Vec2::~Vec2() {

		}

		Vec2& Vec2::add(const Vec2& other) {
			this->x += other.x;
			this->y += other.y;
			
			return *this;
		}

		Vec2& Vec2::substract(const Vec2& other) {
			this->x -= other.x;
			this->y -= other.y;

			return *this;
		}

		Vec2& Vec2::scalarMultiply(const float& scalar) {
			this->x *= scalar;
			this->y *= scalar;

			return *this;
		}

		Vec2& Vec2::scalarDivide(const float& scalar) {
			this->x /= scalar;
			this->y /= scalar;

			return *this;
		}

		bool Vec2::equals(const Vec2& other) {
			return (this->x == other.x && this->y == other.y);
		}

		bool Vec2::notEquals(const Vec2& other) {
			return !(this->equals(other));
		}

		Vec2& Vec2::operator+=(const Vec2& other) {
			return this->add(other);
		}

		Vec2& Vec2::operator-=(const Vec2& other) {
			return this->substract(other);
		}

		Vec2& Vec2::operator*=(const float& other) {
			return this->scalarMultiply(other);
		}

		Vec2& Vec2::operator/=(const float& other) {
			return this->scalarDivide(other);
		}

		float Vec2::dotProduct(const Vec2& other) {
			float result = ((this->x * other.x) + (this->y * other.y));
			return result;
		}

		void Vec2::normalize() {
			this->scalarDivide(this->magnitude());
		}

		float Vec2::magnitude() {
			float x = (float)std::pow(this->x, 2);
			float y = (float)std::pow(this->y, 2);

			return std::sqrt(x + y);
		}

		bool Vec2::operator==(const Vec2& other) {
			return this->equals(other);
		}

		bool Vec2::operator!=(const Vec2& other) {
			return this->notEquals(other);
		}

		Vec2 operator+(Vec2 left, const Vec2& right) {
			return left.add(right);
		}

		Vec2 operator-(Vec2 left, const Vec2& right) {
			return left.substract(right);
		}

		Vec2 operator*(Vec2 vec, const float& scalar) {
			return vec.scalarMultiply(scalar);
		}

		Vec2 operator/(Vec2 vec, const float& scalar) {
			return vec.scalarDivide(scalar);
		}

		float dotProduct(Vec2 left, const Vec2& right) {
			return left.dotProduct(right);
		}

		Vec2 normalize(Vec2 left) {
			return left.scalarDivide(left.magnitude());
		}

		float magnitude(Vec2& vec) {
			return vec.magnitude();
		}

		std::ostream& operator<<(std::ostream& stream, const Vec2& vec) {
			stream << "Vec2: (" << vec.x << ", " << vec.y << ")";
			return stream;
		}

	}
}