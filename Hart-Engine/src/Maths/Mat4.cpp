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
			return Vec3(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
			);
		}

		Vec4 Mat4::multiply(const Vec4& other) const {
			return Vec4(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
			);
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

		Mat4 Mat4::translate(const Vec3& translation) {
			Mat4 result(1.0f);

			result.elements[0 + 3 * COLUMNS] = translation.x;
			result.elements[1 + 3 * COLUMNS] = translation.y;
			result.elements[2 + 3 * COLUMNS] = translation.z;

			return result;
		}

		Mat4 Mat4::rotate(float angleD, const Vec3& axis) {
			Mat4 result(1.0f);

			float angleR = degreeToRadian(angleD);
			float cosTheta = cosR(angleR);
			float sinTheta = sinR(angleR);
			float oneMinusCosTheta = 1.0f - cosTheta;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * COLUMNS] = x * oneMinusCosTheta + cosTheta;
			result.elements[1 + 0 * COLUMNS] = y * x * oneMinusCosTheta + z * sinTheta;
			result.elements[2 + 0 * COLUMNS] = x * z * oneMinusCosTheta - y * sinTheta;

			result.elements[0 + 1 * COLUMNS] = x * y * oneMinusCosTheta - z * sinTheta;
			result.elements[1 + 1 * COLUMNS] = y * oneMinusCosTheta + cosTheta;
			result.elements[2 + 1 * COLUMNS] = y * z * oneMinusCosTheta + x * sinTheta;

			result.elements[0 + 2 * COLUMNS] = x * z * oneMinusCosTheta + y * sinTheta;
			result.elements[1 + 2 * COLUMNS] = y * z * oneMinusCosTheta - x * sinTheta;
			result.elements[2 + 2 * COLUMNS] = z * oneMinusCosTheta + x;

			return result;
		}

		Mat4 Mat4::scale(const Vec3& scale) {
			Mat4 result(1.0f);

			result.elements[0 + 0 * COLUMNS] = scale.x;
			result.elements[1 + 1 * COLUMNS] = scale.y;
			result.elements[2 + 2 * COLUMNS] = scale.z;

			return result;
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
			return left.multiply(right);
		}

		Vec4 operator*(const Mat4& left, const Vec4& right) {
			return left.multiply(right);
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