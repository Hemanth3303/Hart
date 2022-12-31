#include "HartPch.hpp"
#include "Mat4.hpp"

namespace Hart {
	namespace Maths {
		Mat4::Mat4() {
			for (int32_t i = 0; i < 4 * 4; i++) {
				elements[i] = 0.0f;
			}
		}

		Mat4::Mat4(float diagonal) {
			for (int32_t i = 0; i < 4 * 4; i++) {
				elements[i] = 0.0f;
			}
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Mat4::~Mat4() {
		}

		Vec4 Mat4::getColumn(int32_t index) {
			index *= 4;
			return Vec4(
				elements[index + 0],
				elements[index + 1],
				elements[index + 2],
				elements[index + 3]
			);
		}

		Mat4 Mat4::indentity() {
			return Mat4(1.0f);
		}

		Mat4& Mat4::multiply(const Mat4& other) {
			float data[4 * 4];
			for (int32_t y = 0; y < 4; y++) {
				for (int32_t x = 0; x < 4; x++) {
					float sum = 0.0f;
					for (int32_t e = 0; e < 4; e++) {
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					data[x + y * 4] = sum;
				}
			}
			std::memcpy(elements, data, 4 * 4 * sizeof(float));

			return *this;
		}

		Mat4 operator*(Mat4 left, const Mat4& right) {
			return left.multiply(right);
		}

		Mat4& Mat4::operator*=(const Mat4& other) {
			return multiply(other);
		}

		Vec3 Mat4::multiply(const Vec3& vec) const {
			return Vec3(
				columns[0].x * vec.x + columns[1].x * vec.y + columns[2].x * vec.z + columns[3].x,
				columns[0].y * vec.x + columns[1].y * vec.y + columns[2].y * vec.z + columns[3].y,
				columns[0].z * vec.x + columns[1].z * vec.y + columns[2].z * vec.z + columns[3].z
			);
		}

		Vec3 operator*(const Mat4& left, const Vec3& right) {
			return left.multiply(right);
		}

		Vec4 Mat4::multiply(const Vec4& vec) const {
			return Vec4(
				columns[0].x * vec.x + columns[1].x * vec.y + columns[2].x * vec.z + columns[3].x * vec.w,
				columns[0].y * vec.x + columns[1].y * vec.y + columns[2].y * vec.z + columns[3].y * vec.w,
				columns[0].z * vec.x + columns[1].z * vec.y + columns[2].z * vec.z + columns[3].z * vec.w,
				columns[0].w * vec.x + columns[1].w * vec.y + columns[2].w * vec.z + columns[3].w * vec.w
			);
		}

		Vec4 operator*(const Mat4& left, const Vec4& right) {
			return left.multiply(right);
		}

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float, float) {
			return Mat4();
		}

		Mat4 Mat4::perspective(float fov, float aspectRatio, float, float) {
			return Mat4();
		}

		Mat4 Mat4::translate(const Vec3& translationVector) {
			return Mat4();
		}

		Mat4 Mat4::rotate(float angleD, const Vec3& axisVector) {
			return Mat4();
		}

		Mat4 Mat4::scale(const Vec3& scaleVector) {
			return Mat4();
		}
	}
}