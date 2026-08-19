#pragma once

#include "Vec2.hpp"

#include <string>
#include <iostream>

namespace Hart {
	struct Vec3 {
	public:
		// initializes to (0.0f, 0.0f)
		Vec3();
		Vec3(float value);
		Vec3(float px, float py, float pz);
		// creates a Vec3 by using the Vec2's x and y, while setting z to 0
		Vec3(const Vec2& vec2);
		// creates a Vec3 by using the Vec2's x and y, while setting z to pz
		Vec3(const Vec2& vec2, float pz);

		static Vec3 Add(const Vec3& lhs, const Vec3& rhs);
		static Vec3 Subtract(const Vec3& lhs, const Vec3& rhs);
		static Vec3 ScalarMultiply(const Vec3& vec, float scalar);

		static Vec3 Lerp(const Vec3& lhs, const Vec3& rhs, float t);

		static float DotProduct(const Vec3& lhs, const Vec3& rhs);
		static Vec3 CrossProduct(const Vec3& lhs, const Vec3& rhs);
		static float GetMagnitude(const Vec3& vec);
		// returns the normal of given vector without affecting the original vector
		static Vec3 GetNormal(const Vec3& vec);
		// returns the angle between two vectors in radians
		static float GetAngleRBetween(const Vec3& lhs, const Vec3& rhs);
		// returns the angle between two vectors in degrees
		static float GetAngleDBetween(const Vec3& lhs, const Vec3& rhs);

		std::string toString() const;

		friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);

	public:
		float x;
		float y;
		float z;
	};
}
