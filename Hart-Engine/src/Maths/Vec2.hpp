#pragma once

#include <string>
#include <iostream>

namespace Hart {
	struct Vec2 {
	public:
		// initializes to (0.0f, 0.0f)
		Vec2();
		Vec2(float value);
		Vec2(float px, float py);

		static Vec2 Add(const Vec2& lhs, const Vec2& rhs);
		static Vec2 Subtract(const Vec2& lhs, const Vec2& rhs);
		static Vec2 ScalarMultiply(const Vec2& vec, float scalar);

		static Vec2 Lerp(const Vec2& lhs, const Vec2& rhs, float t);

		static float DotProduct(const Vec2& lhs, const Vec2& rhs);
		static float GetMagnitude(const Vec2& vec);
		// returns the normal of given vector without affecting the original vector
		static Vec2 GetNormal(const Vec2& vec);
		// returns the angle between two vectors in radians
		static float GetAngleRBetween(const Vec2& lhs, const Vec2& rhs);
		// returns the angle between two vectors in degrees
		static float GetAngleDBetween(const Vec2& lhs, const Vec2& rhs);

		std::string toString() const;

		friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);

	public:
		float x;
		float y;
	};
}
