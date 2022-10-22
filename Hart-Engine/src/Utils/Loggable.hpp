#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class Loggable {
		public:
			Loggable(const uint8_t& data);
			Loggable(const uint16_t& data);
			Loggable(const uint32_t& data);
			Loggable(const uint64_t& data);
			Loggable(const int8_t& data);
			Loggable(const int16_t& data);
			Loggable(const int32_t& data);
			Loggable(const int64_t& data);
			Loggable(const unsigned long& data);
			Loggable(const long& data);
			Loggable(const float& data);
			Loggable(const double& data);
			Loggable(char* data);
			Loggable(const char* data);
			Loggable(const std::string& data);

			Loggable(const Loggable&) = delete;
			~Loggable();

			friend std::ostream& operator<<(std::ostream& stream, const Loggable& loggable);

		private:
			std::string m_Data;
		};
	}
}