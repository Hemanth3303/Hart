#include "Mat4.hpp"

namespace Hart {
	namespace Maths {

		Mat4::Mat4() {
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					elements[i + j * COLUMNS] = 0;
				}
			}
		}

		Mat4::Mat4(float diagonal) {
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					if (i == j) {
						elements[i + j * COLUMNS] = diagonal;
					}
					else {
						elements[i + j * COLUMNS] = 0;
					}
				}
			}
		}

		Mat4::~Mat4() {

		}

		Mat4& Mat4::add(const Mat4& other) {
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					elements[i + j * COLUMNS] += other.elements[i + j * COLUMNS];
				}
			}
			return *this;
		}

		Mat4& Mat4::substract(const Mat4& other) {
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					elements[i + j * COLUMNS] -= other.elements[i + j * COLUMNS];
				}
			}
			return *this;
		}

		Mat4& Mat4::multiply(const Mat4& other) {
			float data[COLUMNS * ROWS];
			std::memset(data, 0, COLUMNS * ROWS);
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					for (int32_t k = 0; k < COLUMNS; k++) {
						data[i + j * COLUMNS] += elements[i + k * COLUMNS] * other.elements[k + j * COLUMNS];
					}
				}
			}
			std::memcpy(elements, data, COLUMNS * ROWS);
			return *this;
		}

		Mat4& Mat4::operator+=(const Mat4& other) {
			return this->add(other);
		}

		Mat4& Mat4::operator-=(const Mat4& other) {
			return this->substract(other);
		}

		//Mat4& Mat4::operator*=(const Mat4& other) {
		//	// TODO: insert return statement here
		//}

		Mat4& Mat4::transpose() {
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					//TODO
				}
			}
			return *this;
			}

		//Mat4& Mat4::determinant() {
		//	// TODO: insert return statement here
		//}

		Mat4 Mat4::fillWith(float value) {
			Mat4 result;
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					result.elements[i + j * COLUMNS] = value;
				}
			}
			return result;
		}

		Mat4 Mat4::identity() {
			return Mat4(1);
		}

		Mat4 add(Mat4 left, const Mat4& right) {
			return left.add(right);
		}

		Mat4 substract(Mat4 left, const Mat4& right) {
			return left.substract(right);
		}

		Mat4 multiply(Mat4 left, const Mat4& right) {
			return Mat4();
		}

		Mat4 operator+(Mat4 left, const Mat4 right) {
			return add(left, right);
		}

		Mat4 operator-(Mat4 left, const Mat4 right) {
			return substract(left, right);
		}

		Mat4 operator*(Mat4 left, const Mat4 right) {
			return Mat4();
		}

		Mat4 transpose(Mat4& mat) {
			return Mat4();
		}

		float determinant(const Mat4& mat) {
			return 0.0f;
		}

		/*
		* Bruh this is such a mess
		* TODO: Clean this up lmao
		*/
		std::ostream& operator<<(std::ostream& stream, const Mat4& mat) {
			stream << "MAT4: \n[";
			for (int32_t i = 0; i < COLUMNS; i++) {
				if (i != 3) {
					for (int32_t j = 0; j < ROWS; j++) {
						if (i == 0 && j == 0) {
							stream << mat.elements[i + j * COLUMNS] << ", ";
						}
						else {
							stream << " " << mat.elements[i + j * COLUMNS] << ", ";
						}
					}
					stream << "\n";
				}
				else {
					for (int32_t j = 0; j < ROWS; j++) {
						if (j != 3) {
							stream << " " << mat.elements[i + j * COLUMNS] << ", ";
						}
						else {
							stream << " " << mat.elements[i + j * COLUMNS];
						}
					}
				}
			}
			stream << "]";
			return stream;
		}
	}
}