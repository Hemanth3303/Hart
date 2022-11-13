/*
* Utility class used by the Logger to help log all primitive data types and std::string
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Utils {
		class Loggable {
		public:
			Loggable(int8_t value);
			Loggable(int16_t value);
			Loggable(int32_t value);
			Loggable(int64_t value);

			Loggable(uint8_t value);
			Loggable(uint16_t value);
			Loggable(uint32_t value);
			Loggable(uint64_t value);

			Loggable(float value);
			Loggable(double value);

			Loggable(const char* value);
			Loggable(const std::string& value);

			~Loggable();

			friend std::ostream& operator<<(std::ostream& stream, const Loggable& loggable);

		private:
			std::string m_Data;
		};

		std::ostream& operator<<(std::ostream& stream, const Loggable& loggable);
	}
}