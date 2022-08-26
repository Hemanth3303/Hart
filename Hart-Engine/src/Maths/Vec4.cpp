#include "Core/HartPch.hpp"
#include "Vec4.hpp"

namespace Hart {
	namespace Maths {

		Vec4::Vec4() {
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		Vec4::Vec4(const float& x, const float& y, const float& z, const float& w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vec4::Vec4(const Vec2& vec2, const float& z, const float& w) {
			this->x = vec2.x;
			this->y = vec2.y;
			this->z = z;
			this->w = w;
		}

		Vec4::Vec4(const Vec3& vec3, const float& w) {
			this->x = vec3.x;
			this->y = vec3.y;
			this->z = vec3.z;
			this->w = 0;
		}

		Vec4::~Vec4() {

		}

		Vec4& Vec4::add(const Vec4& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;

			return *this;
		}

		Vec4& Vec4::substract(const Vec4& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;

			return *this;
		}

		Vec4& Vec4::scalarMultiply(const float& scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			this->w *= scalar;

			return *this;
		}

		Vec4& Vec4::scalarDivide(const float& scalar) {
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			this->w /= scalar;

			return *this;
		}

		bool Vec4::equals(const Vec4& other) {
			return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
		}

		bool Vec4::notEquals(const Vec4& other) {
			return !(this->equals(other));
		}

		Vec4& Vec4::operator+=(const Vec4& other) {
			return this->add(other);
		}

		Vec4& Vec4::operator-=(const Vec4& other) {
			return this->substract(other);
		}

		Vec4& Vec4::operator*=(const float& other) {
			return this->scalarMultiply(other);
		}

		Vec4& Vec4::operator/=(const float& other) {
			return this->scalarDivide(other);
		}

		float Vec4::dotProduct(const Vec4& other) {
			float result = ((this->x * other.x) + (this->y * other.y) + (this->z * other.z) + (this->w * other.w));
			return result;
		}

		void Vec4::normalize() {
			this->scalarDivide(this->magnitude());
		}

		float Vec4::magnitude() {
			float x = (float)std::pow(this->x, 2);
			float y = (float)std::pow(this->y, 2);
			float z = (float)std::pow(this->z, 2);
			float w = (float)std::pow(this->w, 2);

			return std::sqrt(x + y + z + w);
		}

		bool Vec4::operator==(const Vec4& other) {
			return this->equals(other);
		}

		bool Vec4::operator!=(const Vec4& other) {
			return this->notEquals(other);
		}

		Vec4 operator+(Vec4 left, const Vec4& right) {
			return left.add(right);
		}

		Vec4 operator-(Vec4 left, const Vec4& right) {
			return left.substract(right);
		}

		Vec4 operator*(Vec4 vec, const float& scalar) {
			return vec.scalarMultiply(scalar);
		}

		Vec4 operator/(Vec4 vec, const float& scalar) {
			return vec.scalarDivide(scalar);
		}

		float dotProduct(Vec4 left, const Vec4& right) {
			return left.dotProduct(right);
		}

		Vec4 normalize(Vec4 left) {
			return left.scalarDivide(left.magnitude());
		}

		float magnitude(Vec4& vec) {
			return vec.magnitude();
		}

		std::ostream& operator<<(std::ostream& stream, const Vec4& vec) {
			stream << "Vec4: (" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
			return stream;
		}

	}
}