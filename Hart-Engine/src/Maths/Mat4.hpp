/*
* Basic 4x4 matrix with column major order for opengl
* Functions and Methods for matrix operations also provided
*/

#pragma once

#include "Vec3.hpp"
#include "Vec4.hpp"

#include <iostream>

namespace Hart {
	namespace Maths {
		struct Mat4 {
		public:
			#define COLUMNS (4) 
			#define ROWS (4)
			union {
				float elements[COLUMNS * ROWS];
				Vec4 columns[ROWS];
			};
			
			//initializes all elements to zero
			Mat4();
			//initializes all diagonals to argument value
			Mat4(float diagonal);
			~Mat4();

			Mat4& add(const Mat4& other);
			Mat4& substract(const Mat4& other);
			Mat4& multiply(const Mat4& other);

			Vec3 multiply(const Vec3& other) const;
			Vec4 multiply(const Vec4& other) const;

			Mat4& operator+=(const Mat4& other);
			Mat4& operator-=(const Mat4& other);
			Mat4& operator*=(const Mat4& other);

			//this method transposes the matrix itself
			Mat4& transpose();

			//returns a new Mat4 where all elements are initialized to value
			static Mat4 fillWith(float value);
			//returns a new 4x4 identity matrix
			static Mat4 identity();

			static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static Mat4 perspective(float fov, float aspectRatio, float near, float far);

			static Mat4 translation(const Vec3& translation);
			static Mat4 rotation(float angle, const Vec3& axis);
			static Mat4 scale(const Vec3& scale);

			friend Mat4 add(Mat4 left, const Mat4& right);
			friend Mat4 substract(Mat4 left, const Mat4& right);
			friend Mat4 multiply(Mat4 left, const Mat4& right);

			friend Vec3 operator*(const Mat4& left, const Vec3& right);
			friend Vec4 operator*(const Mat4& left, const Vec4& right);

			friend Mat4 operator+(Mat4 left, const Mat4 right);
			friend Mat4 operator-(Mat4 left, const Mat4 right);
			friend Mat4 operator*(Mat4 left, const Mat4 right);

			//this function transposes a copy of the matrix and return a new transposed matrix
			friend Mat4 transpose(Mat4 mat);

			friend std::ostream& operator<<(std::ostream& stream, const Mat4& mat);

		};
	}
}