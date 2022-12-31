/*
* A 4x4 matrix class
*/

#pragma once

#include "HartPch.hpp"
#include "Vec4.hpp"
#include "MathFunctions.hpp"

namespace Hart {
	namespace Maths {
		struct Mat4 {
		public:
			union {
				float elements[4 * 4];
				Vec4 columns[4];
			};
		public:
			// initializes all elements to zero
			Mat4();
			// initializes all non-diagonal elements to zero, diagonal elements are set to argument value
			Mat4(float diagonal);
			~Mat4();

			// returns a column as a vector
			Vec4 getColumn(int32_t index);

			// creates a new 4x4 identity matrix
			static Mat4 indentity();

			// matrix-matrix multiplication
			Mat4& multiply(const Mat4& other);
			friend Mat4 operator*(Mat4 left, const Mat4& right);
			Mat4& operator*=(const Mat4& other);

			// matrix-Vec3 multiplication
			Vec3 multiply(const Vec3& vec) const;
			friend Vec3 operator*(const Mat4& left, const Vec3& right);

			// matrix-Vec4 multiplication
			Vec4 multiply(const Vec4& vec) const;
			friend Vec4 operator*(const Mat4& left, const Vec4& right);

			// orthographic projection matrix
			static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			// perspective projection matrix
			static Mat4 perspective(float fov, float aspectRatio, float near, float far);

			// transformation operations

			static Mat4 translate(const Vec3& translationVector);
			static Mat4 rotate(float angleD, const Vec3& axisVector);
			static Mat4 scale(const Vec3& scaleVector);
		};
	}
}