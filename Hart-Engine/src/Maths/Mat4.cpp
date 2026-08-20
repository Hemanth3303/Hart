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
		out += ")\n";

		return out;
	}
	Mat4 Mat4::Identity() {
		return Mat4{ 1.0f };
	}

	std::ostream& operator<<(std::ostream& os, const Mat4& mat4) {
		os << mat4.toString();
		return os;
	}
}
