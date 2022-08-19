/*
* Basic 4x4 matrix with column major order for opengl
* Functions and Methods for matrix operations also provided
*/

#pragma once

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

			Mat4& operator+=(const Mat4& other);
			Mat4& operator-=(const Mat4& other);
			Mat4& operator*=(const Mat4& other);

			Mat4& transpose();
			Mat4& determinant();

			//returns a new mat4 where all elements are initialized to value
			static Mat4 fillWith(float value);
			//returns a new 4x4 identity matrix
			static Mat4 identity();

			friend Mat4 add(Mat4 left, const Mat4& right);
			friend Mat4 substract(Mat4 left, const Mat4& right);
			friend Mat4 multiply(Mat4 left, const Mat4& right);

			friend Mat4 operator+(Mat4 left, const Mat4 right);
			friend Mat4 operator-(Mat4 left, const Mat4 right);
			friend Mat4 operator*(Mat4 left, const Mat4 right);

			friend Mat4 transpose(Mat4& mat);
			friend float determinant(const Mat4& mat);

			friend std::ostream& operator<<(std::ostream& stream, const Mat4& mat);

		};
	}
}