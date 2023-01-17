#include "HartPch.hpp"
#include "Vec4.hpp"

namespace Hart {
	namespace Maths {
		Vec4::Vec4() {
			initialize(0.0f, 0.0f, 0.0f, 0.0f);
		}

		Vec4::Vec4(float value) {
			initialize(value, value, value, value);
		}

		Vec4::Vec4(float p_x, float p_y, float p_z, float p_w) {
			initialize(p_x, p_y, p_z, p_w);
		}

		Vec4::Vec4(const Vec2& vec2, float p_z, float p_w) {
			initialize(vec2.x, vec2.y, p_z, p_w);
		}

		Vec4::Vec4(const Vec3& vec3, float p_w) {
			initialize(vec3.x, vec3.y, vec3.z, p_w);
		}

		Vec4 Vec4::normalize() {
			*this = getNormal(*this);
			return *this;
		}

		float Vec4::getMagnitude() {
			return getMagnitude(*this);
		}

		void Vec4::scalarMultiply(float value) {
			*this=scalarMultiply(*this, value);
		}

		Vec4 Vec4::add(const Vec4& left, const Vec4& right) {
			return Vec4(left.x+right.x, left.y+right.y, left.z + right.z, left.w + right.w);
		}

		Vec4 Vec4::subtract(const Vec4& left, const Vec4& right) {
			return Vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
		}

		Vec4 Vec4::scalarMultiply(const Vec4& vec, float k) {
			return Vec4(vec.x * k, vec.y * k, vec.z * k, vec.w * k);
		}

        Vec4& Vec4::add(const Vec4& other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
        }

        Vec4& Vec4::subtract(const Vec4& other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
        }

        Vec4& Vec4::operator+=(const Vec4& other) {
			return this->add(other);
        }

        Vec4& Vec4::operator-=(const Vec4& other) {
			return this->subtract(other);
        }

        float Vec4::dotProduct(const Vec4& left, const Vec4& right) {
			return ((left.x * right.x) + (left.y * right.y) + (left.z * right.z) + (left.w * right.w));
		}

		Vec4 Vec4::getNormal(const Vec4& vec) {
			float magnitude = getMagnitude(vec);
			return Vec4(vec.x / magnitude, vec.y / magnitude, vec.z / magnitude, vec.w / magnitude);
		}

		float Vec4::getAngleRBetween(const Vec4& left, const Vec4& right) {
			// angle = acos(a.b / (|a|*|b|) )
			return static_cast<float>(arcCosR(dotProduct(left, right) / (getMagnitude(left) * getMagnitude(right))));
		}

		float Vec4::getAngleDBetween(const Vec4& left, const Vec4& right) {
			return static_cast<float>(radianToDegrees(getAngleRBetween(left, right)));
		}

		float Vec4::getMagnitude(const Vec4& vec) {
			// sqrt(x^2+y^2+z^2+w^2)
			return static_cast<float>(square_root(power(vec.x, 2) + power(vec.y, 2) + power(vec.z, 2) + power(vec.w, 2)));
		}
		
		const std::string Vec4::toString() const {
			return std::string("Vec4(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")");
		}

		// private
		void Vec4::initialize(float p_x, float p_y, float p_z, float p_w) {
			x = p_x;
			y = p_y;
			z = p_z;
			w = p_w;
		}

        Vec4 operator+(const Vec4& left, const Vec4& right) {
            return Vec4();
        }

        Vec4 operator-(const Vec4& left, const Vec4& right) {
            return Vec4();
        }

        std::ostream& operator<<(std::ostream& stream, Vec4 vec) {
			stream << vec.toString();
			return stream;
		}
	}
}
