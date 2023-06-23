#pragma once

#include "HartPch.hpp"
#include "MathFunctions.hpp"

namespace Hart {
	namespace Maths {
		// A two component vector
		struct Vec2 {
		public:
			float x, y;
		public:
			// initializes x and y components to 0
			Vec2();
			// initializes x and y components to value
			Vec2(float value);
			Vec2(float p_x, float p_y);

			// converts the vector to its normalized form
			Vec2 normalize();
			float getMagnitude();
			// multiplies scalar to current vector
			void scalarMultiply(float value);

			static Vec2 add(const Vec2& left, const Vec2& right);
			static Vec2 subtract(const Vec2& left, const Vec2& right);
			static bool equals(const Vec2& left, const Vec2& right);
			static Vec2 scalarMultiply(const Vec2& vec, float k);

			// adds value to the current vector
			Vec2& add(const Vec2& other);
			// subtracts value from the current vector
			Vec2& subtract(const Vec2& other);
			bool equals(const Vec2& other);

			friend Vec2 operator+(const Vec2& left, const Vec2& right);
			friend Vec2 operator-(const Vec2& left, const Vec2& right);
			friend bool operator==(const Vec2& left, const Vec2& right);

			Vec2& operator+=(const Vec2& other);
			Vec2& operator-=(const Vec2& other);
			bool operator==(const Vec2& other);

			static float dotProduct(const Vec2& left, const Vec2& right);
			// returns the normal of given vector without affecting the original vector
			static Vec2 getNormal(const Vec2& vec);
			// returns the angle between two vectors in radians
			static float getAngleRBetween(const Vec2& left, const Vec2& right);
			// returns the angle between two vectors in degrees
			static float getAngleDBetween(const Vec2& left, const Vec2& right);
			static float getMagnitude(const Vec2& vec);

			friend std::ostream& operator<<(std::ostream&, Vec2 vec);

			const std::string toString() const;

		private:
			void initialize(float p_x, float p_y);
		};
		Vec2 operator+(const Vec2& left, const Vec2& right);
		Vec2 operator-(const Vec2& left, const Vec2& right);
		bool operator==(const Vec2& left, const Vec2& right);
		std::ostream& operator<<(std::ostream& stream, Vec2 vec);
	}
}