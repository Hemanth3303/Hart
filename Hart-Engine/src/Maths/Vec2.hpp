/*
* Two component Vectors and related functions & methods
* dotProduct, magnitude and normalize functions operate on arguments,
* while the same named method variants operate on the instance itself, with extra arguments if required
*/

#pragma once
#include "HartPch.hpp"

namespace Hart {
	namespace Maths {
		struct Vec2 {
		public:
			float x, y;
			
			Vec2();
			Vec2(const float& x, const float& y);
			~Vec2();

			Vec2& add(const Vec2& other);
			Vec2& substract(const Vec2& other);
			Vec2& scalarMultiply(const float& scalar);
			Vec2& scalarDivide(const float& scalar);


			bool equals(const Vec2& other);
			bool notEquals(const Vec2& other);

			Vec2& operator+=(const Vec2& other);
			Vec2& operator-=(const Vec2& other);
			Vec2& operator*=(const float& other);
			Vec2& operator/=(const float& other);

			float dotProduct(const Vec2& other);
			void normalize();
			float magnitude();

			bool operator==(const Vec2& other);
			bool operator!=(const Vec2& other);

			std::string toString();

			friend Vec2 operator+(Vec2 left, const Vec2& right);
			friend Vec2 operator-(Vec2 left, const Vec2& right);
			friend Vec2 operator*(Vec2 vec, const float& scalar);
			friend Vec2 operator/(Vec2 vec, const float& scalar);

			friend float dotProduct(Vec2 left, const Vec2& right);
			friend Vec2 normalize(Vec2 left);
			friend float magnitude(Vec2& vec);

			friend std::ostream& operator<<(std::ostream& stream, const Vec2& vec);

		private:
			
		};
	}
}