#pragma once

#include "Vec4.hpp"
#include "Vec3.hpp"

#include <string>
#include <cstddef>

namespace Hart {
	// opengl style column major matrix_4x4
	// each column can be accessed as a Hart::Vec4
	struct Mat4 {
		inline static constexpr size_t MAT4_WIDTH = 4;
		inline static constexpr size_t MAT4_HEIGHT = 4;
		union {
			float elements[MAT4_WIDTH * MAT4_HEIGHT];
			Vec4 columns[MAT4_WIDTH];
		};

		// initializes all elements to 0.0f
		Mat4();
		// initialized principal diagonal elements to provided argument;
		// rest are initialized to 0.0f
		Mat4(float diagonal);
		/**
		 * initialize all elements as in the initializer list provided.
		 * must provide in column major order.
		 * must be exactly 16 values, else will be zero initialized only.
		 * note that matrix will look exactly as it is provided in the initializer list,
		 * ie, if m =
		 *		 {1, 3,
		 *		  2, 4}
		 * then printing m will give
		 *	 [1, 3,
		 *	  2, 4]
		 */
		Mat4(const std::initializer_list<float>& values);

		float getElementAt(size_t row, size_t column) const;
		// returns a column as a Hart::Vec4
		Vec4 getColumn(size_t index) const;

		// returns a new 4x4 identity matrix
		static Mat4 Identity();

		// basic matrix maths

		static Mat4 Add(const Mat4& lhs, const Mat4& rhs);
		static Mat4 Subtract(const Mat4& lhs, const Mat4& rhs);
		static Mat4 ScalarMultiply(const Mat4& mat4, float scalar);
		static Mat4 Multiply(const Mat4& lhs, const Mat4& rhs);

		// matrix vector simple operations

		static Vec4 Multiply(const Mat4& mat4, const Vec4& vec4);
		static Vec3 Multiply(const Mat4& mat4, const Vec3& vec3);

		// matrix inverse related operations

		static Mat4 Transpose(const Mat4& mat4);
		static float Determinant(const Mat4& mat4);
		static Mat4 Cofactor(const Mat4& mat4);
		static Mat4 Adjoint(const Mat4& mat4);
		static Mat4 Inverse(const Mat4& mat4);

		// matrix camera operations

		// returns orthographic projection matrix
		static Mat4 Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
		// returns perspective projection matrix (provide field of view angle in degrees)
		static Mat4 Perspective(float fieldOfViewD, float aspectRatio, float nearPlane, float farPlane);

		// matrix vector transformation operations

		static Mat4 Translate(const Vec3& translationVector);
		// provide angle in degrees
		static Mat4 Rotate(float angleD, const Vec3& axisVector);
		static Mat4 Scale(const Vec3& scaleVector);

		// camera utilities

		static Mat4 LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& worldUpDirection);

		// this will print as column major ordering
		std::string toString() const;
		
		friend std::ostream& operator<<(std::ostream& os, const Mat4& mat4);
	};
}

/**
 * note to self.
 * num rows = height
 * num coloumns = width
 */
