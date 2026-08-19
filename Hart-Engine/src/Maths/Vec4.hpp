#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"

#include <string>
#include <iostream>

namespace Hart {
	struct Vec4 {
	public:
		// initializes to (0.0f, 0.0f)
		Vec4();
		Vec4(float value);
		Vec4(float px, float py, float pz, float pw);
		// creates a Vec4 by using the Vec2's x and y, while setting z and w to 0
		Vec4(const Vec2& vec2);
		// creates a Vec4 by using the Vec2's x and y, while setting z and w to value
		Vec4(const Vec2& vec2, float value);
		// creates a Vec4 by using the Vec2's x and y, while setting z to pz and w to pz
		Vec4(const Vec2& vec2, float pz, float pw);
		// creates a Vec4 by using the Vec2's x and y, while setting w to 0
		Vec4(const Vec3& vec3);
		// creates a Vec4 by using the Vec2's x and y, while setting w to pw
		Vec4(const Vec3& vec3, float pw);

		static Vec4 Add(const Vec4& lhs, const Vec4& rhs);
		static Vec4 Subtract(const Vec4& lhs, const Vec4& rhs);
		static Vec4 ScalarMultiply(const Vec4& vec, float scalar);
		static Vec4 ComponentWiseMultiplication(const Vec4& lhs, const Vec4& rhs);

		static Vec4 Lerp(const Vec4& lhs, const Vec4& rhs, float t);

		static float DotProduct(const Vec4& lhs, const Vec4& rhs);
		static float GetMagnitude(const Vec4& vec);
		// returns the normal of given vector without affecting the original vector
		static Vec4 GetNormal(const Vec4& vec);
		// returns the angle between two vectors in radians
		static float GetAngleRBetween(const Vec4& lhs, const Vec4& rhs);
		// returns the angle between two vectors in degrees
		static float GetAngleDBetween(const Vec4& lhs, const Vec4& rhs);

		std::string toString() const;

		friend std::ostream& operator<<(std::ostream& os, const Vec4& vec);

	public:
		float x;
		float y;
		float z;
		float w;
	};
}
