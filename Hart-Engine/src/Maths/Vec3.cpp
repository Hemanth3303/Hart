#include "HartPch.hpp"
#include "Vec3.hpp"

namespace Hart {
	namespace Maths {
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
			*this = getNormal(*this);
			return *this;
		}

		float Vec3::getMagnitude() {
			return getMagnitude(*this);
		}

		const Vec3& Vec3::scalarMultiply(float value) {
			*this=scalarMultiply(*this, value);
			return *this;
		}

		Vec3 Vec3::add(const Vec3& left, const Vec3& right) {
			return Vec3(left.x + right.x, left.y + right.y, left.z + right.z);
		}

		Vec3 Vec3::subtract(const Vec3& left, const Vec3& right) {
			return Vec3(left.x - right.x, left.y - right.y, left.z - right.z);
		}

        bool Vec3::equals(const Vec3& left, const Vec3& right) {
			return (left.x == right.x && left.y == right.y && left.z == right.z);
        }

		Vec3 Vec3::scalarMultiply(const Vec3& vec, float k) {
			return Vec3(vec.x * k, vec.y * k, vec.z * k);
		}

        Vec3 Vec3::lerp(const Vec3& a, const Vec3& b, float t) {
			return Vec3(
				static_cast<float>(Maths::lerp(a.x, b.x, t)),
				static_cast<float>(Maths::lerp(a.y, b.y, t)),
				static_cast<float>(Maths::lerp(a.z, b.z, t))
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
			return Vec3::equals(*this, other);
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

        float Vec3::dotProduct(const Vec3& left, const Vec3& right) {
			return ((left.x * right.x) + (left.y * right.y) + (left.z * right.z));
		}

		Vec3 Vec3::crossProduct(const Vec3& left, const Vec3& right) {
			return Vec3(
				(left.y * right.z) - (right.y * left.z),
				(left.x * right.z) - (right.x * left.z),
				(left.x * right.y) - (right.x * left.y)
			);
		}

		Vec3 Vec3::getNormal(const Vec3& vec) {
			float magnitude = getMagnitude(vec);
			return Vec3(vec.x/magnitude, vec.y/magnitude, vec.z / magnitude);
		}

		float Vec3::getAngleRBetween(const Vec3& left, const Vec3& right) {
			// angle = acos(a.b / (|a|*|b|) )
			return static_cast<float>(arcCosR(dotProduct(left, right) / (getMagnitude(left) * getMagnitude(right))));
		}

		float Vec3::getAngleDBetween(const Vec3& left, const Vec3& right) {
			return static_cast<float>(radianToDegrees(getAngleRBetween(left, right)));
		}

		float Vec3::getMagnitude(const Vec3& vec) {
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
			return Vec3::add(left, right);
        }

        Vec3 operator-(const Vec3& left, const Vec3& right) {
            return Vec3::subtract(left, right);
        }

        bool operator==(const Vec3& left, const Vec3& right) {
			return Vec3::equals(left, right);
        }

        std::ostream& operator<<(std::ostream& stream, Vec3 vec) {
			stream << vec.toString();
			return stream;
		}
	}
}
