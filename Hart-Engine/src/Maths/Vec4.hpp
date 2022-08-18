/*
* Four component Vectors and related functions & methods
* dotProduct, magnitude and normalize functions operate on arguments,
* while the same named method variants operate on the instance itself, with extra arguments if required
*/

#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"

#include <iostream>
#include <cmath>

namespace Hart {
	namespace Maths {
		class Vec4 {
		public:
			float x, y, z, w;

			Vec4();
			Vec4(const float& x, const float& y, const float& z, const float& w = 0);
			Vec4(const Vec2& vec2, const float& z = 0, const float& w = 0);
			Vec4(const Vec3& vec3, const float& w = 0);
			~Vec4();

			Vec4& add(const Vec4& other);
			Vec4& substract(const Vec4& other);
			Vec4& scalarMultiply(const float& scalar);
			Vec4& scalarDivide(const float& scalar);


			bool equals(const Vec4& other);
			bool notEquals(const Vec4& other);

			Vec4& operator+=(const Vec4& other);
			Vec4& operator-=(const Vec4& other);
			Vec4& operator*=(const float& other);
			Vec4& operator/=(const float& other);

			float dotProduct(const Vec4& other);
			void normalize();
			float magnitude();

			bool operator==(const Vec4& other);
			bool operator!=(const Vec4& other);

			friend Vec4 operator+(Vec4 left, const Vec4& right);
			friend Vec4 operator-(Vec4 left, const Vec4& right);
			friend Vec4 operator*(Vec4 vec, const float& scalar);
			friend Vec4 operator/(Vec4 vec, const float& scalar);

			friend float dotProduct(Vec4 left, const Vec4& right);
			friend Vec4 normalize(Vec4 left);
			friend float magnitude(Vec4& vec);

			friend std::ostream& operator<<(std::ostream& stream, const Vec4& vec);

		private:

		};
	}
}