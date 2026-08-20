#include "HartPch.hpp"
#include "Mat4.hpp"
#include "MathFunctions.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"

#include <algorithm>
#include <iterator>

namespace Hart {
	float determinant3x3(
		float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22);

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

	Vec4 Mat4::MultiplyVec4(const Mat4& mat4, const Vec4& vec4) {
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

	Vec3 Mat4::MultiplyVec3(const Mat4& mat4, const Vec3& vec3) {
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

	Mat4 Mat4::Transpose(const Mat4& mat4) {
		Mat4 result;

		for (size_t column = 0; column < MAT4_WIDTH; column++) {
			for (size_t row = 0; row < MAT4_HEIGHT; row++) {
				result.elements[row * MAT4_HEIGHT + column] =
					mat4.elements[column * MAT4_HEIGHT + row];
			}
		}

		return result;
	}

	float Mat4::Determinant(const Mat4& mat4) {
		const float a00 = mat4.getElementAt(0, 0);
		const float a01 = mat4.getElementAt(0, 1);
		const float a02 = mat4.getElementAt(0, 2);
		const float a03 = mat4.getElementAt(0, 3);

		const float a10 = mat4.getElementAt(1, 0);
		const float a11 = mat4.getElementAt(1, 1);
		const float a12 = mat4.getElementAt(1, 2);
		const float a13 = mat4.getElementAt(1, 3);

		const float a20 = mat4.getElementAt(2, 0);
		const float a21 = mat4.getElementAt(2, 1);
		const float a22 = mat4.getElementAt(2, 2);
		const float a23 = mat4.getElementAt(2, 3);

		const float a30 = mat4.getElementAt(3, 0);
		const float a31 = mat4.getElementAt(3, 1);
		const float a32 = mat4.getElementAt(3, 2);
		const float a33 = mat4.getElementAt(3, 3);

		const float d0 = determinant3x3(
			a11, a12, a13,
			a21, a22, a23,
			a31, a32, a33);

		const float d1 = determinant3x3(
			a10, a12, a13,
			a20, a22, a23,
			a30, a32, a33);

		const float d2 = determinant3x3(
			a10, a11, a13,
			a20, a21, a23,
			a30, a31, a33);

		const float d3 = determinant3x3(
			a10, a11, a12,
			a20, a21, a22,
			a30, a31, a32);

		return ((a00 * d0) -
				(a01 * d1) +
				(a02 * d2) -
				(a03 * d3));
	}

	Mat4 Mat4::Cofactor(const Mat4& mat4) {
		/**
		 * cofactor pattern for mat4x4
		 *  +  -  +  -
		 *  -  +  -  +
		 *  +  -  +  -
		 *  -  +  -  +
		 */

		Mat4 result;

		const float a00 = mat4.getElementAt(0, 0);
		const float a01 = mat4.getElementAt(0, 1);
		const float a02 = mat4.getElementAt(0, 2);
		const float a03 = mat4.getElementAt(0, 3);

		const float a10 = mat4.getElementAt(1, 0);
		const float a11 = mat4.getElementAt(1, 1);
		const float a12 = mat4.getElementAt(1, 2);
		const float a13 = mat4.getElementAt(1, 3);

		const float a20 = mat4.getElementAt(2, 0);
		const float a21 = mat4.getElementAt(2, 1);
		const float a22 = mat4.getElementAt(2, 2);
		const float a23 = mat4.getElementAt(2, 3);

		const float a30 = mat4.getElementAt(3, 0);
		const float a31 = mat4.getElementAt(3, 1);
		const float a32 = mat4.getElementAt(3, 2);
		const float a33 = mat4.getElementAt(3, 3);

		// C00
		result.elements[0 * MAT4_HEIGHT + 0] =
			determinant3x3(
				a11, a12, a13,
				a21, a22, a23,
				a31, a32, a33);

		// C01
		result.elements[1 * MAT4_HEIGHT + 0] =
			-determinant3x3(
				a10, a12, a13,
				a20, a22, a23,
				a30, a32, a33);

		// C02
		result.elements[2 * MAT4_HEIGHT + 0] =
			determinant3x3(
				a10, a11, a13,
				a20, a21, a23,
				a30, a31, a33);

		// C03
		result.elements[3 * MAT4_HEIGHT + 0] =
			-determinant3x3(
				a10, a11, a12,
				a20, a21, a22,
				a30, a31, a32);

		// C10
		result.elements[0 * MAT4_HEIGHT + 1] =
			-determinant3x3(
				a01, a02, a03,
				a21, a22, a23,
				a31, a32, a33);

		// C11
		result.elements[1 * MAT4_HEIGHT + 1] =
			determinant3x3(
				a00, a02, a03,
				a20, a22, a23,
				a30, a32, a33);

		// C12
		result.elements[2 * MAT4_HEIGHT + 1] =
			-determinant3x3(
				a00, a01, a03,
				a20, a21, a23,
				a30, a31, a33);

		// C13
		result.elements[3 * MAT4_HEIGHT + 1] =
			determinant3x3(
				a00, a01, a02,
				a20, a21, a22,
				a30, a31, a32);

		// C20
		result.elements[0 * MAT4_HEIGHT + 2] =
			determinant3x3(
				a01, a02, a03,
				a11, a12, a13,
				a31, a32, a33);

		// C21
		result.elements[1 * MAT4_HEIGHT + 2] =
			-determinant3x3(
				a00, a02, a03,
				a10, a12, a13,
				a30, a32, a33);

		// C22
		result.elements[2 * MAT4_HEIGHT + 2] =
			determinant3x3(
				a00, a01, a03,
				a10, a11, a13,
				a30, a31, a33);

		// C23
		result.elements[3 * MAT4_HEIGHT + 2] =
			-determinant3x3(
				a00, a01, a02,
				a10, a11, a12,
				a30, a31, a32);

		// C30
		result.elements[0 * MAT4_HEIGHT + 3] =
			-determinant3x3(
				a01, a02, a03,
				a11, a12, a13,
				a21, a22, a23);

		// C31
		result.elements[1 * MAT4_HEIGHT + 3] =
			determinant3x3(
				a00, a02, a03,
				a10, a12, a13,
				a20, a22, a23);

		// C32
		result.elements[2 * MAT4_HEIGHT + 3] =
			-determinant3x3(
				a00, a01, a03,
				a10, a11, a13,
				a20, a21, a23);

		// C33
		result.elements[3 * MAT4_HEIGHT + 3] =
			determinant3x3(
				a00, a01, a02,
				a10, a11, a12,
				a20, a21, a22);

		return result;
	}

	Mat4 Mat4::Adjoint(const Mat4& mat4) {
		return Transpose(Cofactor(mat4));
	}

	Mat4 Mat4::Inverse(const Mat4& mat4) {
		float determinant = Determinant(mat4);
		HART_DEBUG_ASSERT((determinant != 0.0f),
						  "Reason: The given matrix is not invertible, ",
						  "as determinant==0");
		if (determinant == 0.0f) {
			HART_ENGINE_ERROR("determinant = ", determinant,
							  ". The given matrix is not invertible.",
							  "\n\treturning back input matrix");
			return mat4;
		}

		return ScalarMultiply(Adjoint(mat4), (1.0f / determinant));
	}

	Mat4 Mat4::OrthographicProjectionMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
		Mat4 result(1.0f);

		result.elements[0 * MAT4_HEIGHT + 0] = 2.0f / (right - left);
		result.elements[1 * MAT4_HEIGHT + 1] = 2.0f / (top - bottom);
		result.elements[2 * MAT4_HEIGHT + 2] = 2.0f / (nearPlane - farPlane);

		result.elements[3 * MAT4_HEIGHT + 0] = (left + right) / (left - right);
		result.elements[3 * MAT4_HEIGHT + 1] = (bottom + top) / (bottom - top);
		result.elements[3 * MAT4_HEIGHT + 2] = (farPlane + nearPlane) / (farPlane - nearPlane);

		return result;
	}

	Mat4 Mat4::PerspectiveProjectionMatrix(float fieldOfViewD, float aspectRatio, float nearPlane, float farPlane) {
		Mat4 result(1.0f);

		float q = 1.0f / static_cast<float>(Hart::tanD(0.5 * fieldOfViewD));
		float a = q / aspectRatio;
		float b = (nearPlane + farPlane) / (nearPlane - farPlane);
		float c = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);

		result.elements[0 * MAT4_HEIGHT + 0] = a;
		result.elements[1 * MAT4_HEIGHT + 1] = q;
		result.elements[2 * MAT4_HEIGHT + 2] = b;
		result.elements[2 * MAT4_HEIGHT + 3] = -1.0f;
		result.elements[3 * MAT4_HEIGHT + 2] = c;

		return result;
	}

	Mat4 Mat4::Translate(const Vec3& translationVector) {
		Mat4 result(1.0f);

		result.elements[3 * MAT4_HEIGHT + 0] = translationVector.x;
		result.elements[3 * MAT4_HEIGHT + 1] = translationVector.y;
		result.elements[3 * MAT4_HEIGHT + 2] = translationVector.z;

		return result;
	}

	Mat4 Mat4::Rotate(float angleD, const Vec3& axisVector) {
		Mat4 result(1.0f);

		float cosAngleD = static_cast<float>(Hart::cosD(angleD));
		float sinAngleD = static_cast<float>(Hart::sinD(angleD));
		float oneMinusCosAngleD = 1.0f - cosAngleD;

		float x = axisVector.x;
		float y = axisVector.y;
		float z = axisVector.z;

		result.elements[0 * MAT4_HEIGHT + 0] = x * x * oneMinusCosAngleD + cosAngleD;
		result.elements[1 * MAT4_HEIGHT + 0] = y * x * oneMinusCosAngleD + z * sinAngleD;
		result.elements[2 * MAT4_HEIGHT + 0] = z * x * oneMinusCosAngleD - y * sinAngleD;

		result.elements[0 * MAT4_HEIGHT + 1] = x * y * oneMinusCosAngleD - z * sinAngleD;
		result.elements[1 * MAT4_HEIGHT + 1] = y * y * oneMinusCosAngleD + cosAngleD;
		result.elements[2 * MAT4_HEIGHT + 1] = z * y * oneMinusCosAngleD + x * sinAngleD;

		result.elements[0 * MAT4_HEIGHT + 2] = x * z * oneMinusCosAngleD + y * sinAngleD;
		result.elements[1 * MAT4_HEIGHT + 2] = y * z * oneMinusCosAngleD - x * sinAngleD;
		result.elements[2 * MAT4_HEIGHT + 2] = z * z * oneMinusCosAngleD + cosAngleD;

		return result;
	}

	Mat4 Mat4::Scale(const Vec3& scaleVector) {
		Mat4 result(1.0f);

		result.elements[0 * MAT4_HEIGHT + 0] = scaleVector.x;
		result.elements[1 * MAT4_HEIGHT + 1] = scaleVector.y;
		result.elements[2 * MAT4_HEIGHT + 2] = scaleVector.z;

		return result;
	}

	Mat4 Mat4::LookAt(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& worldUpDirection) {
		// calculate cameraDirection
		Vec3 zAxis = Vec3::GetNormal(Vec3::Subtract(cameraPosition, targetPosition));
		// get position of right axiz vector
		Vec3 xAxis = Vec3::GetNormal(Vec3::CrossProduct(Vec3::GetNormal(worldUpDirection), zAxis));
		// calculate camera up vector
		Vec3 yAxis = Vec3::CrossProduct(zAxis, xAxis);

		// Create translation and rotation matrix
		Mat4 translation = Mat4::Translate(Vec3::ScalarMultiply(cameraPosition, -1.0f));

		Mat4 rotation = Mat4::Identity();
		rotation.elements[0 * MAT4_HEIGHT + 0] = xAxis.x;
		rotation.elements[1 * MAT4_HEIGHT + 0] = xAxis.y;
		rotation.elements[2 * MAT4_HEIGHT + 0] = xAxis.z;

		rotation.elements[0 * MAT4_HEIGHT + 1] = yAxis.x;
		rotation.elements[1 * MAT4_HEIGHT + 1] = yAxis.y;
		rotation.elements[2 * MAT4_HEIGHT + 1] = yAxis.z;

		rotation.elements[0 * MAT4_HEIGHT + 2] = -zAxis.x;
		rotation.elements[1 * MAT4_HEIGHT + 2] = -zAxis.y;
		rotation.elements[2 * MAT4_HEIGHT + 2] = -zAxis.z;

		return Mat4::Multiply(rotation, translation);
	}

	float determinant3x3(
		float a00, float a01, float a02,
		float a10, float a11, float a12,
		float a20, float a21, float a22) {
		return a00 * (a11 * a22 - a12 * a21) -
			   a01 * (a10 * a22 - a12 * a20) +
			   a02 * (a10 * a21 - a11 * a20);
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

	std::ostream& operator<<(std::ostream& os, const Mat4& mat4) {
		os << mat4.toString();
		return os;
	}

}
