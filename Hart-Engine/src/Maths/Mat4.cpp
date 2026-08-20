#include "HartPch.hpp"
#include "Mat4.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"

#include <algorithm>
#include <iterator>
#include <cstring>

namespace Hart {
	Mat4::Mat4() {
		std::fill(std::begin(elements), std::end(elements), 0.0f);
	}

	Mat4::Mat4(float diagonal) {
		std::fill(std::begin(elements), std::end(elements), 0.0f);

		elements[0 * MAT4_HEIGHT + 0] = diagonal;
		elements[1 * MAT4_HEIGHT + 1] = diagonal;
		elements[2 * MAT4_HEIGHT + 2] = diagonal;
		elements[3 * MAT4_HEIGHT + 3] = diagonal;
	}

	Mat4::Mat4(const std::initializer_list<float>& values) {
		std::fill(std::begin(elements), std::end(elements), 0.0f);
		size_t expectedSize = MAT4_WIDTH * MAT4_HEIGHT;
		size_t gotSize = values.size();
		HART_DEBUG_ASSERT(gotSize == expectedSize,
						  "Reason: Must provide exactly 16 elements. No more, no less.");
		if (gotSize != expectedSize) {
			HART_ENGINE_ERROR(
				"Expected ", expectedSize, " elements.",
				"\n\tGot ", gotSize, " instead.",
				"\n\tZero intializing matrix instead");
			return;
		}

		std::copy(values.begin(), values.end(), std::begin(elements));
	}

	float Mat4::getElementAt(size_t row, size_t column) const {
		HART_DEBUG_ASSERT(row < MAT4_HEIGHT, "invalid row");
		HART_DEBUG_ASSERT(column < MAT4_WIDTH, "invalid column");
		return elements[column * MAT4_HEIGHT + row];
	}

	Vec4 Mat4::getColumn(size_t index) const {
		HART_DEBUG_ASSERT(index < MAT4_WIDTH, "invalid vector index");
		index *= 4;
		return Vec4{
			elements[index + 0],
			elements[index + 1],
			elements[index + 2],
			elements[index + 3]
		};
	}

	std::string Mat4::toString() const {
		std::string out = "Mat4(\n";

		for (size_t column = 0; column < MAT4_WIDTH; column++) {
			out += "[ ";
			for (size_t row = 0; row < MAT4_HEIGHT; row++) {
				out += std::to_string(elements[column * MAT4_HEIGHT + row]) + ", ";
			}
			out += "]\n";
		}
		out += ")";

		return out;
	}
	Mat4 Mat4::Identity() {
		return Mat4(1.0f);
	}

	Mat4 Mat4::Add(const Mat4& lhs, const Mat4& rhs) {
		Mat4 result;
		for (size_t column = 0; column < MAT4_WIDTH; column++) {
			for (size_t row = 0; row < MAT4_HEIGHT; row++) {
				result.elements[column * MAT4_HEIGHT + row] =
					lhs.elements[column * MAT4_HEIGHT + row] +
					rhs.elements[column * MAT4_HEIGHT + row];
			}
		}
		return result;
	}

	Mat4 Mat4::Subtract(const Mat4& lhs, const Mat4& rhs) {
		Mat4 result;
		for (size_t column = 0; column < MAT4_WIDTH; column++) {
			for (size_t row = 0; row < MAT4_HEIGHT; row++) {
				result.elements[column * MAT4_HEIGHT + row] =
					lhs.elements[column * MAT4_HEIGHT + row] -
					rhs.elements[column * MAT4_HEIGHT + row];
			}
		}
		return result;
	}

	Mat4 Mat4::ScalarMultiply(const Mat4& mat4, float scalar) {
		Mat4 result;
		for (size_t i = 0; i < (MAT4_WIDTH * MAT4_HEIGHT); i++) {
			result.elements[i] = mat4.elements[i] * scalar;
		}
		return result;
	}

	Mat4 Mat4::Multiply(const Mat4& lhs, const Mat4& rhs) {
		Mat4 result;

		for (size_t column = 0; column < MAT4_WIDTH; column++) {
			for (size_t row = 0; row < MAT4_HEIGHT; row++) {
				float sum = 0.0f;

				for (size_t k = 0; k < MAT4_WIDTH; k++) {
					sum += lhs.elements[k * MAT4_HEIGHT + row] *
						   rhs.elements[column * MAT4_WIDTH + k];
				}
				result.elements[column * MAT4_HEIGHT + row] = sum;
			}
		}

		return result;
	}

	Vec4 Mat4::Multiply(const Mat4& mat4, const Vec4& vec4) {
		return Vec4{
			mat4.columns[0].x * vec4.x +
				mat4.columns[1].x * vec4.y +
				mat4.columns[2].x * vec4.z +
				mat4.columns[3].x * vec4.w,

			mat4.columns[0].y * vec4.x +
				mat4.columns[1].y * vec4.y +
				mat4.columns[2].y * vec4.z +
				mat4.columns[3].y * vec4.w,

			mat4.columns[0].z * vec4.x +
				mat4.columns[1].z * vec4.y +
				mat4.columns[2].z * vec4.z +
				mat4.columns[3].z * vec4.w,

			mat4.columns[0].w * vec4.x +
				mat4.columns[1].w * vec4.y +
				mat4.columns[2].w * vec4.z +
				mat4.columns[3].w * vec4.w
		};
	}

	Vec3 Mat4::Multiply(const Mat4& mat4, const Vec3& vec3) {
		return Vec3{
			mat4.columns[0].x * vec3.x +
				mat4.columns[1].x * vec3.y +
				mat4.columns[2].x * vec3.z +
				mat4.columns[3].x,

			mat4.columns[0].y * vec3.x +
				mat4.columns[1].y * vec3.y +
				mat4.columns[2].y * vec3.z +
				mat4.columns[3].y,

			mat4.columns[0].z * vec3.x +
				mat4.columns[1].z * vec3.y +
				mat4.columns[2].z * vec3.z +
				mat4.columns[3].z
		};
	}

	std::ostream& operator<<(std::ostream& os, const Mat4& mat4) {
		os << mat4.toString();
		return os;
	}
}
