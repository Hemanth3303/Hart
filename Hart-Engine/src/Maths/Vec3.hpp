#pragma once

#include "HartPch.hpp"
#include "Vec2.hpp"
#include "MathFunctions.hpp"

namespace Hart {
	// A three component vector.
	// This class has an additional crossProduct() method
	struct Vec3 {
	public:
		float x, y, z;
	public:
		// initializes x, y and z components to 0
		Vec3();
		// initializes x, y and z components to value
		Vec3(float value);
		Vec3(float p_x, float p_y, float p_z = 0);
		// creates a Vec3 by using the Vec2's x and y, while setting z to p_z
		Vec3(const Vec2& vec2, float p_z = 0);

		// converts the vector to its normalized form
		const Vec3& normalize();
		float getMagnitude();
		const Vec3& scalarMultiply(float value);

		static Vec3 add(const Vec3& left, const Vec3& right);
		static Vec3 subtract(const Vec3& left, const Vec3& right);
		static bool equals(const Vec3& left, const Vec3& right);
		static Vec3 scalarMultiply(const Vec3& vec, float k);

		static Vec3 lerp(const Vec3& a, const Vec3& b, float t);

		// adds value to the current vector
		Vec3& add(const Vec3& other);
		// subtracts value from the current vector
		Vec3& subtract(const Vec3& other);
		bool equals(const Vec3& other);

		friend Vec3 operator+(const Vec3& left, const Vec3& right);
		friend Vec3 operator-(const Vec3& left, const Vec3& right);
		friend bool operator==(const Vec3& left, const Vec3& right);

		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		bool operator==(const Vec3& other);

		static float dotProduct(const Vec3& left, const Vec3& right);
		static Vec3 crossProduct(const Vec3& left, const Vec3& right);
		// returns the normal of given vector without affecting the original vector
		static Vec3 getNormal(const Vec3& vec);
		// returns the angle between two vectors in radians
		static float getAngleRBetween(const Vec3& left, const Vec3& right);
		// returns the angle between two vectors in degrees
		static float getAngleDBetween(const Vec3& left, const Vec3& right);
		static float getMagnitude(const Vec3& vec);

		friend std::ostream& operator<<(std::ostream&, Vec3 vec);

		const std::string toString() const;

	private:
		void initialize(float p_x, float p_y, float p_z);
	};
	Vec3 operator+(const Vec3& left, const Vec3& right);
	Vec3 operator-(const Vec3& left, const Vec3& right);
	bool operator==(const Vec3& left, const Vec3& right);
	std::ostream& operator<<(std::ostream& stream, Vec3 vec);
}