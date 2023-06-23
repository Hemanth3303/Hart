#include "HartPch.hpp"
#include "Loggable.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"

namespace Hart {
	namespace Utils {
		Loggable::Loggable(std::int8_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(std::int16_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(std::int32_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(std::int64_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(std::uint8_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(std::uint16_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(std::uint32_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(std::uint64_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(float value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(double value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(const char* value) {
			m_Data = std::string(value);
		}

		Loggable::Loggable(const unsigned char* value) {
			m_Data = std::string(reinterpret_cast<const char*>(value));
		}

		Loggable::Loggable(char* value) {
			m_Data = std::string(value);
		}

		Loggable::Loggable(unsigned char* value) {
			m_Data = std::string(reinterpret_cast<char*>(value));
		}

		Loggable::Loggable(const std::string& value) {
			m_Data = value;
		}

		Loggable::Loggable(std::string_view value) {
			m_Data = value;
		}


		Loggable::Loggable(const Maths::Vec2& vec) {
			m_Data = vec.toString();
		}

		Loggable::Loggable(const Maths::Vec3& vec) {
			m_Data = vec.toString();
		}

		Loggable::Loggable(const Maths::Vec4& vec) {
			m_Data = vec.toString();
		}

		Loggable::Loggable(const Maths::Mat4& matrix) {
			m_Data = matrix.toString();
		}

		Loggable::Loggable(const Events::Event& e) {
			m_Data = e.toString();
		}

		Loggable::~Loggable() {

		}

		std::ostream& operator<<(std::ostream& stream, const Loggable& loggable) {
			stream << loggable.m_Data;
			return stream;
		}
	}
}