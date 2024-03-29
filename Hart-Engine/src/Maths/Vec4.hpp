#pragma once

#include "HartPch.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "MathFunctions.hpp"

namespace Hart {
	// A four component vector
	struct Vec4 {
	public:
		float x, y, z, w;
	public:
		// initializes x, y, z and w components to 0
		Vec4();
		// initializes x, y, z and w components to value
		Vec4(float value);
		Vec4(float p_x, float p_y, float p_z = 0, float p_w = 0);
		// creates a Vec4 by using the Vec2's x and y, while setting z to p_z and w to p_w
		Vec4(const Vec2& vec2, float p_z = 0, float p_w = 0);
		// creates a Vec4 by using the Vec3's x, y and z, while setting w to p_w
		Vec4(const Vec3& vec3, float p_w = 0);

		// converts the vector to its normalized form
		const Vec4& normalize();
		float getMagnitude();
		const Vec4& scalarMultiply(float value);

		static Vec4 Add(const Vec4& left, const Vec4& right);
		static Vec4 Subtract(const Vec4& left, const Vec4& right);
		static bool Equals(const Vec4& left, const Vec4& right);
		// usefull for colors
		static Vec4 ComponentWiseMultiplication(const Vec4& left, const Vec4& right);
		static Vec4 ScalarMultiply(const Vec4& vec, float k);

		static Vec4 Lerp(const Vec4& a, const Vec4& b, float t);

		// adds value to the current vector
		Vec4& add(const Vec4& other);
		// subtracts value from the current vector
		Vec4& subtract(const Vec4& other);
		bool equals(const Vec4& other);
		// usefull for colors
		Vec4& componentWiseMultiplication(const Vec4& other);

		friend Vec4 operator+(const Vec4& left, const Vec4& right);
		friend Vec4 operator-(const Vec4& left, const Vec4& right);
		// performs component wise multiplication
		friend Vec4 operator*(const Vec4& left, const Vec4& right);
		friend bool operator==(const Vec4& left, const Vec4& right);

		Vec4& operator+=(const Vec4& other);
		Vec4& operator-=(const Vec4& other);
		// performs component wise multiplication
		Vec4& operator*=(const Vec4& other);
		bool operator==(const Vec4& other);

		static float DotProduct(const Vec4& left, const Vec4& right);
		// returns the normal of given vector without affecting the original vector
		static Vec4 GetNormal(const Vec4& vec);
		// returns the angle between two vectors in radians
		static float GetAngleRBetween(const Vec4& left, const Vec4& right);
		// returns the angle between two vectors in degrees
		static float GetAngleDBetween(const Vec4& left, const Vec4& right);
		static float GetMagnitude(const Vec4& vec);

		friend std::ostream& operator<<(std::ostream&, Vec4 vec);

		const std::string toString() const;

	private:
		void initialize(float p_x, float p_y, float p_z, float p_w);
	};
	Vec4 operator+(const Vec4& left, const Vec4& right);
	Vec4 operator-(const Vec4& left, const Vec4& right);
	Vec4 operator*(const Vec4& left, const Vec4& right);
	bool operator==(const Vec4& left, const Vec4& right);
	std::ostream& operator<<(std::ostream& stream, Vec4 vec);
}