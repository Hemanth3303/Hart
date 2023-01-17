#include "HartPch.hpp"
#include "Vec2.hpp"

namespace Hart {
	namespace Maths {
		Vec2::Vec2() {
			initialize(0.0f, 0.0f);
		}

		Vec2::Vec2(float value) {
			initialize(value, value);
		}

		Vec2::Vec2(float p_x, float p_y) {
			initialize(p_x, p_y);
		}

		Vec2 Vec2::normalize() {
			*this = getNormal(*this);
			return *this;
		}

		float Vec2::getMagnitude() {
			return getMagnitude(*this);
		}

		void Vec2::scalarMultiply(float value) {
			*this=scalarMultiply(*this, value);
		}

		Vec2 Vec2::add(const Vec2& left, const Vec2& right) {
			return Vec2(left.x+right.x, left.y+right.y);
		}

		Vec2 Vec2::subtract(const Vec2& left, const Vec2& right) {
			return Vec2(left.x - right.x, left.y - right.y);
		}

		Vec2 Vec2::scalarMultiply(const Vec2& vec, float k) {
			return Vec2(vec.x * k, vec.y * k);
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

		Vec2& Vec2::operator+=(const Vec2& other) {
			return this->add(other);
		}

		Vec2& Vec2::operator-=(const Vec2& other) {
			return this->subtract(other);
		}

		float Vec2::dotProduct(const Vec2& left, const Vec2& right) {
			return ((left.x * right.x) + (left.y * right.y));
		}

		Vec2 Vec2::getNormal(const Vec2& vec) {
			float magnitude = getMagnitude(vec);
			return Vec2(vec.x/magnitude, vec.y/magnitude);
		}

		float Vec2::getAngleRBetween(const Vec2& left, const Vec2& right) {
			// angle = acos(a.b / (|a|*|b|) )
			return static_cast<float>(arcCosR(dotProduct(left, right) / (getMagnitude(left) * getMagnitude(right))));
		}

		float Vec2::getAngleDBetween(const Vec2& left, const Vec2& right) {
			return static_cast<float>(radianToDegrees(getAngleRBetween(left, right)));
		}

		float Vec2::getMagnitude(const Vec2& vec) {
			// sqrt(x^2+y^2)
			return static_cast<float>(square_root(power(vec.x, 2) + power(vec.y, 2)));
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
			return Vec2::add(left, right);
		}

		Vec2 operator-(const Vec2& left, const Vec2& right) {
			return Vec2::subtract(left, right);
		}

		std::ostream& operator<<(std::ostream& stream, Vec2 vec) {
			stream << vec.toString();
			return stream;
		}
	}
}
