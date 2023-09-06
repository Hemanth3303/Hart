/*
* A 4x4 matrix class
*/

#pragma once

#include "HartPch.hpp"
#include "Vec4.hpp"
#include "MathFunctions.hpp"

namespace Hart {
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
		/*
		initialize all elements as in the initializer list provided
		note that matrix will look exactly as it is provided in the initializer list
		ie, if m=
				 {1, 2,
				  3, 4}
		then printing m will give
			 [1, 2,
			  3, 4]
		*/
		Mat4(const std::initializer_list<float>& values);
		~Mat4();

		// returns a column as a vector
		Vec4 getColumn(std::int32_t index);

		// returns element at aij of A
		float getElementAt(std::int32_t i, std::int32_t j) const;

		// creates a new 4x4 identity matrix
		static Mat4 Identity();

		// converts a matrix to a string for printing
		std::string toString() const;

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

		// transposes the current matrix, and returns it. The original is modified
		Mat4& transpose();
		// returns the determinant of the current matrix object
		const float determinant();
		// returns the adjoint(adjugate) of the the matrix and modifies it
		Mat4& adjoint();
		// inverses the current matrix, and returns it. The original is modified
		Mat4& inverse();

		// orthographic projection matrix
		static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		// perspective projection matrix(angle in degrees)
		static Mat4 Perspective(float fovD, float aspectRatio, float near, float far);

		// returns the transpose of given matrix
		static Mat4 Transpose(const Mat4& matrix);
		// returns the determinant of the given matrix
		static const float Determinant(const Mat4& matrix);
		// returns the adjoint(adjugate) of the the given matrix without modifiying it
		static Mat4 Adjoint(const Mat4& matrix);
		// returns the inverse of given matrix
		static Mat4 Inverse(const Mat4& matrix);

		// transformation operations

		static Mat4 Translate(const Vec3& translationVector);
		static Mat4 Rotate(float angleD, const Vec3& axisVector);
		static Mat4 Scale(const Vec3& scaleVector);

		// camera utils

		// returns a view matrix
		static Mat4 LookAt(const Vec3& position, const Vec3& target, const Vec3& worldUp);

		friend std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);
	};
	Mat4 operator*(Mat4 left, const Mat4& right);
	Vec3 operator*(const Mat4& left, const Vec3& right);
	Vec4 operator*(const Mat4& left, const Vec4& right);

	std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);
}