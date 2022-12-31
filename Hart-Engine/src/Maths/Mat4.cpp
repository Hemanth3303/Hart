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

		std::string Mat4::toString() const {
			std::string out = "Mat4(\n";
			for (int32_t i = 0; i < 4; i++) {
				out += "[ ";
				for (int32_t j = 0; j < 4; j++) {
					out += std::to_string(elements[i + j * 4]) + ", ";
				}
				out += "]\n";
			}
			out += ")\n";
			return out;
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

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}

		Mat4 Mat4::perspective(float fovD, float aspectRatio, float near, float far) {
			Mat4 result(1.0f);

			float q = 1.0f / tanD(0.5f * fovD);
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;
		}

		Mat4 Mat4::translate(const Vec3& translationVector) {
			Mat4 result(1.0f);

			result.elements[0 + 3 * 4] = translationVector.x;
			result.elements[1 + 3 * 4] = translationVector.y;
			result.elements[2 + 3 * 4] = translationVector.z;

			return result;
		}

		Mat4 Mat4::rotate(float angleD, const Vec3& axisVector) {
			Mat4 result(1.0f);

			float cosX = cosD(angleD);
			float sinX = sinD(angleD);
			float oneMinusCosX = 1.0f - cosX;

			float x = axisVector.x;
			float y = axisVector.y;
			float z = axisVector.z;

			result.elements[0 + 0 * 4] = x * oneMinusCosX + cosX;
			result.elements[1 + 0 * 4] = y * x * oneMinusCosX + z * sinX;
			result.elements[2 + 0 * 4] = x * z * oneMinusCosX - y * sinX;

			result.elements[0 + 1 * 4] = x * y * oneMinusCosX - z * sinX;
			result.elements[1 + 1 * 4] = y * oneMinusCosX + cosX;
			result.elements[2 + 1 * 4] = y * z * oneMinusCosX + x * sinX;

			result.elements[0 + 2 * 4] = x * z * oneMinusCosX + y * sinX;
			result.elements[1 + 2 * 4] = y * z * oneMinusCosX - x * sinX;
			result.elements[2 + 2 * 4] = z * oneMinusCosX + cosX;

			return result;
		}

		Mat4 Mat4::scale(const Vec3& scaleVector) {
			Mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scaleVector.x;
			result.elements[1 + 1 * 4] = scaleVector.y;
			result.elements[2 + 2 * 4] = scaleVector.z;

			return result;
		}

		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix) {
			stream << matrix.toString();
			return stream;
		}
	}
}