#pragma once

#include "Vec2.hpp"

#include <iostream>
#include <cmath>

namespace Hart {
	namespace Maths {
		class Vec3 {
		public:
			float x, y, z;

			Vec3();
			Vec3(const float& x, const float& y, const float& z = 0);
			Vec3(const Vec2& vec2, const float& z = 0);
			~Vec3();

			Vec3& add(const Vec3& other);
			Vec3& substract(const Vec3& other);
			Vec3& scalarMultiply(const float& scalar);
			Vec3& scalarDivide(const float& scalar);


			bool equals(const Vec3& other);
			bool notEquals(const Vec3& other);

			Vec3& operator+=(const Vec3& other);
			Vec3& operator-=(const Vec3& other);
			Vec3& operator*=(const float& other);
			Vec3& operator/=(const float& other);

			float dotProduct(const Vec3& other);
			Vec3 crossProduct(const Vec3& other);
			void normalize();
			float magnitude();

			bool operator==(const Vec3& other);
			bool operator!=(const Vec3& other);

			friend Vec3 operator+(Vec3 left, const Vec3& right);
			friend Vec3 operator-(Vec3 left, const Vec3& right);
			friend Vec3 operator*(Vec3 vec, const float& scalar);
			friend Vec3 operator/(Vec3 vec, const float& scalar);

			friend float dotProduct(Vec3 left, const Vec3& right);
			friend Vec3 crossProduct(Vec3 left, const Vec3& right);
			friend Vec3 normalize(Vec3 left);
			friend float magnitude(Vec3& vec);

			friend std::ostream& operator<<(std::ostream& stream, const Vec3& vec);

		private:

		};
	}
}