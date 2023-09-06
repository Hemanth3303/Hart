#include "HartPch.hpp"
#include "Mat4.hpp"

namespace Hart {
	Mat4::Mat4() {
		for (std::int32_t i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}
	}

	Mat4::Mat4(float diagonal) {
		for (std::int32_t i = 0; i < 4 * 4; i++) {
			elements[i] = 0.0f;
		}
		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	Mat4::Mat4(const std::initializer_list<float>& values) {
		HART_ASSERT_EQUAL(values.size(), 16, "Reason: Must provide exactly 16 elements to the constructor method Mat4(const std::initializer_list<float>& values)");
		const float* itr = values.begin();
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				elements[j * 4 + i] = *itr;
				itr++;
			}
		}
	}

	Mat4::~Mat4() {

	}

	Vec4 Mat4::getColumn(std::int32_t index) {
		index *= 4;
		return Vec4(
			elements[index + 0],
			elements[index + 1],
			elements[index + 2],
			elements[index + 3]
		);
	}

	float Mat4::getElementAt(std::int32_t i, std::int32_t j) const {
		return elements[i + j * 4];
	}

	Mat4 Mat4::Identity() {
		return Mat4(1.0f);
	}

	std::string Mat4::toString() const {
		std::string out = "Mat4(\n";
		for (std::int32_t i = 0; i < 4; i++) {
			out += "[ ";
			for (std::int32_t j = 0; j < 4; j++) {
				out += std::to_string(elements[i + j * 4]) + ", ";
			}
			out += "]\n";
		}
		out += ")\n";
		return out;
	}

	Mat4& Mat4::multiply(const Mat4& other) {
		float data[4 * 4]{};
		for (std::int32_t y = 0; y < 4; y++) {
			for (std::int32_t x = 0; x < 4; x++) {
				float sum = 0.0f;
				for (std::int32_t e = 0; e < 4; e++) {
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		std::memcpy(elements, data, static_cast<std::size_t>(4) * 4 * sizeof(float));

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

	Mat4& Mat4::transpose() {
		*this = Transpose(*this);
		return *this;
	}

	const float Mat4::determinant() {
		return Determinant(*this);
	}

	Mat4& Mat4::adjoint() {
		*this = Adjoint(*this);
		return *this;
	}

	Mat4& Mat4::inverse() {
		*this = Inverse(*this);
		return *this;
	}

	Vec4 operator*(const Mat4& left, const Vec4& right) {
		return left.multiply(right);
	}

	Mat4 Mat4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
		Mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	Mat4 Mat4::Perspective(float fovD, float aspectRatio, float near, float far) {
		Mat4 result(1.0f);

		float q = 1.0f / static_cast<float>(tanD(0.5 * static_cast<double>(fovD)));
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

	Mat4 Mat4::Transpose(const Mat4& matrix) {
		Mat4 result;
		for (std::int32_t y = 0; y < 4; y++) {
			for (std::int32_t x = 0; x < 4; x++) {
				result.elements[x * 4 + y] = matrix.elements[x + y * 4];
			}
		}
		return result;
	}

	const float Mat4::Determinant(const Mat4& matrix) {
		const float* e = matrix.elements;

		float cofactor0 =
			e[5] * (e[10] * e[15] - e[11] * e[14]) -
			e[9] * (e[6] * e[15] - e[7] * e[14]) +
			e[13] * (e[6] * e[11] - e[7] * e[10]);

		float cofactor1 =
			e[4] * (e[10] * e[15] - e[11] * e[14]) -
			e[8] * (e[6] * e[15] - e[7] * e[14]) +
			e[12] * (e[6] * e[11] - e[7] * e[10]);

		float cofactor2 =
			e[4] * (e[9] * e[15] - e[11] * e[13]) -
			e[8] * (e[5] * e[15] - e[7] * e[13]) +
			e[12] * (e[5] * e[11] - e[7] * e[9]);

		float cofactor3 =
			e[4] * (e[9] * e[14] - e[10] * e[13]) -
			e[8] * (e[5] * e[14] - e[6] * e[13]) +
			e[12] * (e[5] * e[10] - e[6] * e[9]);

		// Calculate the determinant
		return (e[0] * cofactor0 - e[1] * cofactor1 + e[2] * cofactor2 - e[3] * cofactor3);
	}

	Mat4 Mat4::Adjoint(const Mat4& matrix) {
		Mat4 adjointMatrix;

		adjointMatrix.elements[0] =
			matrix.elements[5] * (matrix.elements[10] * matrix.elements[15] - matrix.elements[11] * matrix.elements[14]) -
			matrix.elements[6] * (matrix.elements[9] * matrix.elements[15] - matrix.elements[11] * matrix.elements[13]) +
			matrix.elements[7] * (matrix.elements[9] * matrix.elements[14] - matrix.elements[10] * matrix.elements[13]);

		adjointMatrix.elements[1] =
			-(matrix.elements[1] * (matrix.elements[10] * matrix.elements[15] - matrix.elements[11] * matrix.elements[14]) -
				matrix.elements[2] * (matrix.elements[9] * matrix.elements[15] - matrix.elements[11] * matrix.elements[13]) +
				matrix.elements[3] * (matrix.elements[9] * matrix.elements[14] - matrix.elements[10] * matrix.elements[13]));

		adjointMatrix.elements[2] =
			matrix.elements[1] * (matrix.elements[6] * matrix.elements[15] - matrix.elements[7] * matrix.elements[14]) -
			matrix.elements[2] * (matrix.elements[5] * matrix.elements[15] - matrix.elements[7] * matrix.elements[13]) +
			matrix.elements[3] * (matrix.elements[5] * matrix.elements[14] - matrix.elements[6] * matrix.elements[13]);

		adjointMatrix.elements[3] =
			-(matrix.elements[1] * (matrix.elements[6] * matrix.elements[11] - matrix.elements[7] * matrix.elements[10]) -
				matrix.elements[2] * (matrix.elements[5] * matrix.elements[11] - matrix.elements[7] * matrix.elements[9]) +
				matrix.elements[3] * (matrix.elements[5] * matrix.elements[10] - matrix.elements[6] * matrix.elements[9]));

		adjointMatrix.elements[4] =
			-(matrix.elements[4] * (matrix.elements[10] * matrix.elements[15] - matrix.elements[11] * matrix.elements[14]) -
				matrix.elements[6] * (matrix.elements[8] * matrix.elements[15] - matrix.elements[11] * matrix.elements[12]) +
				matrix.elements[7] * (matrix.elements[8] * matrix.elements[14] - matrix.elements[10] * matrix.elements[12]));

		adjointMatrix.elements[5] =
			matrix.elements[0] * (matrix.elements[10] * matrix.elements[15] - matrix.elements[11] * matrix.elements[14]) -
			matrix.elements[2] * (matrix.elements[8] * matrix.elements[15] - matrix.elements[11] * matrix.elements[12]) +
			matrix.elements[3] * (matrix.elements[8] * matrix.elements[14] - matrix.elements[10] * matrix.elements[12]);

		adjointMatrix.elements[6] =
			-(matrix.elements[0] * (matrix.elements[6] * matrix.elements[15] - matrix.elements[7] * matrix.elements[14]) -
				matrix.elements[2] * (matrix.elements[4] * matrix.elements[15] - matrix.elements[7] * matrix.elements[12]) +
				matrix.elements[3] * (matrix.elements[4] * matrix.elements[14] - matrix.elements[6] * matrix.elements[12]));

		adjointMatrix.elements[7] =
			matrix.elements[0] * (matrix.elements[6] * matrix.elements[11] - matrix.elements[7] * matrix.elements[10]) -
			matrix.elements[2] * (matrix.elements[4] * matrix.elements[11] - matrix.elements[7] * matrix.elements[8]) +
			matrix.elements[3] * (matrix.elements[4] * matrix.elements[10] - matrix.elements[6] * matrix.elements[8]);

		adjointMatrix.elements[8] =
			matrix.elements[4] * (matrix.elements[9] * matrix.elements[15] - matrix.elements[11] * matrix.elements[13]) -
			matrix.elements[5] * (matrix.elements[8] * matrix.elements[15] - matrix.elements[11] * matrix.elements[12]) +
			matrix.elements[7] * (matrix.elements[8] * matrix.elements[13] - matrix.elements[9] * matrix.elements[12]);

		adjointMatrix.elements[9] =
			-(matrix.elements[0] * (matrix.elements[9] * matrix.elements[15] - matrix.elements[11] * matrix.elements[13]) -
				matrix.elements[1] * (matrix.elements[8] * matrix.elements[15] - matrix.elements[11] * matrix.elements[12]) +
				matrix.elements[3] * (matrix.elements[8] * matrix.elements[13] - matrix.elements[9] * matrix.elements[12]));

		adjointMatrix.elements[10] =
			matrix.elements[0] * (matrix.elements[5] * matrix.elements[15] - matrix.elements[7] * matrix.elements[13]) -
			matrix.elements[1] * (matrix.elements[4] * matrix.elements[15] - matrix.elements[7] * matrix.elements[12]) +
			matrix.elements[3] * (matrix.elements[4] * matrix.elements[13] - matrix.elements[5] * matrix.elements[12]);

		adjointMatrix.elements[11] =
			-(matrix.elements[0] * (matrix.elements[5] * matrix.elements[11] - matrix.elements[7] * matrix.elements[9]) -
				matrix.elements[1] * (matrix.elements[4] * matrix.elements[11] - matrix.elements[7] * matrix.elements[8]) +
				matrix.elements[3] * (matrix.elements[4] * matrix.elements[9] - matrix.elements[5] * matrix.elements[8]));

		adjointMatrix.elements[12] =
			-(matrix.elements[4] * (matrix.elements[9] * matrix.elements[14] - matrix.elements[10] * matrix.elements[13]) -
				matrix.elements[5] * (matrix.elements[8] * matrix.elements[14] - matrix.elements[10] * matrix.elements[12]) +
				matrix.elements[6] * (matrix.elements[8] * matrix.elements[13] - matrix.elements[9] * matrix.elements[12]));

		adjointMatrix.elements[13] =
			matrix.elements[0] * (matrix.elements[9] * matrix.elements[14] - matrix.elements[10] * matrix.elements[13]) -
			matrix.elements[1] * (matrix.elements[8] * matrix.elements[14] - matrix.elements[10] * matrix.elements[12]) +
			matrix.elements[2] * (matrix.elements[8] * matrix.elements[13] - matrix.elements[9] * matrix.elements[12]);

		adjointMatrix.elements[14] =
			-(matrix.elements[0] * (matrix.elements[5] * matrix.elements[14] - matrix.elements[6] * matrix.elements[13]) -
				matrix.elements[1] * (matrix.elements[4] * matrix.elements[14] - matrix.elements[6] * matrix.elements[12]) +
				matrix.elements[2] * (matrix.elements[4] * matrix.elements[13] - matrix.elements[5] * matrix.elements[12]));

		adjointMatrix.elements[15] =
			matrix.elements[0] * (matrix.elements[5] * matrix.elements[10] - matrix.elements[6] * matrix.elements[9]) -
			matrix.elements[1] * (matrix.elements[4] * matrix.elements[10] - matrix.elements[6] * matrix.elements[8]) +
			matrix.elements[2] * (matrix.elements[4] * matrix.elements[9] - matrix.elements[5] * matrix.elements[8]);

		return adjointMatrix;
	}

	Mat4 Mat4::Inverse(const Mat4& matrix) {
		const float deter = Determinant(matrix);
		HART_ASSERT_NOT_EQUAL(deter, 0, "Reason: The given matrix is not invertible, as determinant==0");

		if (deter == 0.0f) {
			return matrix;
		}

		Mat4 inverseMat = Adjoint(matrix);
		for (std::int32_t i = 0; i < 4 * 4; i++) {
			inverseMat.elements[i] /= deter;
		}

		return inverseMat;
	}

	Mat4 Mat4::Translate(const Vec3& translationVector) {
		Mat4 result(1.0f);

		result.elements[0 + 3 * 4] = translationVector.x;
		result.elements[1 + 3 * 4] = translationVector.y;
		result.elements[2 + 3 * 4] = translationVector.z;

		return result;
	}

	Mat4 Mat4::Rotate(float angleD, const Vec3& axisVector) {
		Mat4 result(1.0f);

		float cosAngleD = static_cast<float>(cosD(angleD));
		float sinAngleD = static_cast<float>(sinD(angleD));
		float oneMinusCosAngleD = 1.0f - cosAngleD;

		float x = axisVector.x;
		float y = axisVector.y;
		float z = axisVector.z;

		result.elements[0 + 0 * 4] = x * x * oneMinusCosAngleD + cosAngleD;
		result.elements[1 + 0 * 4] = y * x * oneMinusCosAngleD + z * sinAngleD;
		result.elements[2 + 0 * 4] = z * x * oneMinusCosAngleD - y * sinAngleD;

		result.elements[0 + 1 * 4] = x * y * oneMinusCosAngleD - z * sinAngleD;
		result.elements[1 + 1 * 4] = y * y * oneMinusCosAngleD + cosAngleD;
		result.elements[2 + 1 * 4] = z * y * oneMinusCosAngleD + x * sinAngleD;

		result.elements[0 + 2 * 4] = x * z * oneMinusCosAngleD + y * sinAngleD;
		result.elements[1 + 2 * 4] = y * z * oneMinusCosAngleD - x * sinAngleD;
		result.elements[2 + 2 * 4] = z * z * oneMinusCosAngleD + cosAngleD;

		return result;
	}

	Mat4 Mat4::Scale(const Vec3& scaleVector) {
		Mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scaleVector.x;
		result.elements[1 + 1 * 4] = scaleVector.y;
		result.elements[2 + 2 * 4] = scaleVector.z;

		return result;
	}

	Mat4 Mat4::LookAt(const Vec3& position, const Vec3& target, const Vec3& worldUp) {
		// calculate cameraDirection
		Vec3 zAxis = Vec3::GetNormal(position - target);
		// get position of right axiz vector
		Vec3 xAxis = Vec3::GetNormal(Vec3::CrossProduct(Vec3::GetNormal(worldUp), zAxis));
		// calculate camera up vector
		Vec3 yAxis = Vec3::CrossProduct(zAxis, xAxis);

		// Create translation and rotation matrix
		Mat4 translation = Mat4::Identity();
		translation.elements[0 + 3 * 4] = -position.x;
		translation.elements[1 + 3 * 4] = -position.y;
		translation.elements[2 + 3 * 4] = -position.z;
		Mat4 rotation = Mat4::Identity();
		rotation.elements[0 + 0 * 4] = xAxis.x;
		rotation.elements[1 + 0 * 4] = xAxis.y;
		rotation.elements[2 + 0 * 4] = xAxis.z;
		rotation.elements[0 + 1 * 4] = yAxis.x;
		rotation.elements[1 + 1 * 4] = yAxis.y;
		rotation.elements[2 + 1 * 4] = yAxis.z;
		rotation.elements[0 + 2 * 4] = -zAxis.x;
		rotation.elements[1 + 2 * 4] = -zAxis.y;
		rotation.elements[2 + 2 * 4] = -zAxis.z;

		return (rotation * translation);
	}

	std::ostream& operator<<(std::ostream& stream, const Mat4& matrix) {
		stream << matrix.toString();
		return stream;
	}
}