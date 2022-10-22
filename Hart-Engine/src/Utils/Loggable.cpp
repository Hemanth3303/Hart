#include "HartPch.hpp"
#include "Loggable.hpp"

namespace Hart {
	namespace Utils {
		Loggable::Loggable(const uint8_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const uint16_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const uint32_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const uint64_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const int8_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const int16_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const int32_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const int64_t& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const unsigned long& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const long& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const float& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(const double& data) {
			m_Data = std::to_string(data);
		}

		Loggable::Loggable(char* data) {
			m_Data = std::string(data);
		}

		Loggable::Loggable(const char* data) {
			m_Data = std::string(data);
		}

		Loggable::Loggable(const std::string& data) {
			m_Data = data;
		}

		Loggable::~Loggable() {

		}

		std::ostream& operator<<(std::ostream& stream, const Loggable& loggable) {
			stream << loggable.m_Data;
			return stream;
		}
	}
}