#include "Core/HartPch.hpp"
#include "Vec3.hpp"

namespace Hart {
	namespace Maths {

		Vec3::Vec3() {
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		Vec3::Vec3(const float& x, const float& y, const float& z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vec3::Vec3(const Vec2& vec2, const float& z) {
			this->x = vec2.x;
			this->y = vec2.y;
			this->z = z;
		}

		Vec3::~Vec3() {

		}

		Vec3& Vec3::add(const Vec3& other) {
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;

			return *this;
		}

		Vec3& Vec3::substract(const Vec3& other) {
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;

			return *this;
		}

		Vec3& Vec3::scalarMultiply(const float& scalar) {
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;

			return *this;
		}

		Vec3& Vec3::scalarDivide(const float& scalar) {
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;

			return *this;
		}

		bool Vec3::equals(const Vec3& other) {
			return (this->x == other.x && this->y == other.y && this->z == other.z);
		}

		bool Vec3::notEquals(const Vec3& other) {
			return !(this->equals(other));
		}

		Vec3& Vec3::operator+=(const Vec3& other) {
			return this->add(other);
		}

		Vec3& Vec3::operator-=(const Vec3& other) {
			return this->substract(other);
		}

		Vec3& Vec3::operator*=(const float& other) {
			return this->scalarMultiply(other);
		}

		Vec3& Vec3::operator/=(const float& other) {
			return this->scalarDivide(other);
		}

		float Vec3::dotProduct(const Vec3& other) {
			return((this->x * other.x) + (this->y * other.y) + (this->z * other.z));
		}

		Vec3 Vec3::crossProduct(const Vec3& other) {
			Vec3 out;
			out.x = ((this->y * other.z) - (other.y * this->z));
			out.y = -((this->x * other.z) - (other.x * this->z));
			out.z = ((this->x * other.y) - (other.x * this->y));

			return out;
		}

		void Vec3::normalize() {
			this->scalarDivide(this->magnitude());
		}

		float Vec3::magnitude() {
			float x = (float)std::pow(this->x, 2);
			float y = (float)std::pow(this->y, 2);
			float z = (float)std::pow(this->z, 2);

			return std::sqrt(x + y + z);
		}

		bool Vec3::operator==(const Vec3& other) {
			return this->equals(other);
		}

		bool Vec3::operator!=(const Vec3& other) {
			return this->notEquals(other);
		}

		std::string Vec3::toString() {
			std::string outString;
			outString.append("Vec3: (");
			outString.append(std::to_string(x));
			outString.append(", ");
			outString.append(std::to_string(y));
			outString.append(", ");
			outString.append(std::to_string(z));
			outString.append(")");
			return outString;
		}

		Vec3 operator+(Vec3 left, const Vec3& right) {
			return left.add(right);
		}

		Vec3 operator-(Vec3 left, const Vec3& right) {
			return left.substract(right);
		}

		Vec3 operator*(Vec3 vec, const float& scalar) {
			return vec.scalarMultiply(scalar);
		}

		Vec3 operator/(Vec3 vec, const float& scalar) {
			return vec.scalarDivide(scalar);
		}

		float dotProduct(Vec3 left, const Vec3& right) {
			return left.dotProduct(right);
		}

		Vec3 crossProduct(Vec3 left, const Vec3& right) {
			return left.crossProduct(right);
		}

		Vec3 normalize(Vec3 left) {
			return left.scalarDivide(left.magnitude());
		}

		float magnitude(Vec3& vec) {
			return vec.magnitude();
		}

		std::ostream& operator<<(std::ostream& stream, const Vec3& vec) {
			stream << "Vec3: (" << vec.x << ", " << vec.y << ", " << vec.z << ")";
			return stream;
		}

	}
}