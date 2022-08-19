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
			std::memset(data, 0, COLUMNS * ROWS * sizeof(float));
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = 0; j < ROWS; j++) {
					for (int32_t k = 0; k < COLUMNS; k++) {
						data[i + j * COLUMNS] += elements[i + k * COLUMNS] * other.elements[k + j * COLUMNS];
					}
				}
			}
			std::memcpy(elements, data, COLUMNS * ROWS * sizeof(float));
			return *this;
		}

		Vec3 Mat4::multiply(const Vec3& other) const {
			return Vec3();
		}

		Vec4 Mat4::multiply(const Vec4& other) const {
			return Vec4();
		}

		Mat4& Mat4::operator+=(const Mat4& other) {
			return this->add(other);
		}

		Mat4& Mat4::operator-=(const Mat4& other) {
			return this->substract(other);
		}

		Mat4& Mat4::operator*=(const Mat4& other) {
			return this->multiply(other);
		}

		Mat4& Mat4::transpose() {
			float temp;
			for (int32_t i = 0; i < COLUMNS; i++) {
				for (int32_t j = i; j < ROWS; j++) {
					temp = elements[i * COLUMNS + j];
					elements[i * COLUMNS + j] = elements[i + j * COLUMNS];
					elements[i + j * COLUMNS] = temp;
				}
			}
			return *this;
		}

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

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float, float) {
			return Mat4();
		}

		Mat4 Mat4::perspective(float fov, float aspectRatio, float, float) {
			return Mat4();
		}

		Mat4 Mat4::translation(const Vec3& translation) {
			return Mat4();
		}

		Mat4 Mat4::rotation(float angle, const Vec3& axis) {
			return Mat4();
		}

		Mat4 Mat4::scale(const Vec3& scale) {
			return Mat4();
		}

		Mat4 add(Mat4 left, const Mat4& right) {
			return left.add(right);
		}

		Mat4 substract(Mat4 left, const Mat4& right) {
			return left.substract(right);
		}

		Mat4 multiply(Mat4 left, const Mat4& right) {
			return left.multiply(right);
		}

		Vec3 operator*(const Mat4& left, const Vec3& right) {
			return Vec3();
		}

		Vec4 operator*(const Mat4& left, const Vec4& right) {
			return Vec4();
		}

		Mat4 operator+(Mat4 left, const Mat4 right) {
			return add(left, right);
		}

		Mat4 operator-(Mat4 left, const Mat4 right) {
			return substract(left, right);
		}

		Mat4 operator*(Mat4 left, const Mat4 right) {
			return multiply(left, right);
		}

		Mat4 transpose(Mat4 mat) {
			return mat.transpose();
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