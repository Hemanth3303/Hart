#include "HartPch.hpp"
#include "Loggable.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	namespace Utils {
		Loggable::Loggable(int8_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(int16_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(int32_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(int64_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(uint8_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(uint16_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(uint32_t value) {
			m_Data = std::to_string(value);
		}

		Loggable::Loggable(uint64_t value) {
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

		Loggable::Loggable(const std::string& value) {
			m_Data = value;
		}

		Loggable::Loggable(const Maths::Vec2& vec) {
			m_Data = vec.toString();
		}

		Loggable::~Loggable() {

		}

		std::ostream& operator<<(std::ostream& stream, const Loggable& loggable) {
			stream << loggable.m_Data;
			return stream;
		}
	}
}