/*
* Utility class used by the Logger to help log different types, including primitivies and Hart objects
*/

#pragma once

#include "HartPch.hpp"
#include "Events/Event.hpp"

namespace Hart {

	namespace Maths {
		struct Vec2;
		struct Vec3;
		struct Vec4;
		struct Mat4;
	}

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
			Loggable(const unsigned char* value);
			Loggable(char* value);
			Loggable(unsigned char* value);
			Loggable(const std::string& value);

			Loggable(const Maths::Vec2& vec);
			Loggable(const Maths::Vec3& vec);
			Loggable(const Maths::Vec4& vec);

			Loggable(const Maths::Mat4& matrix);
			Loggable(const Events::Event& e);

			~Loggable();

			friend std::ostream& operator<<(std::ostream& stream, const Loggable& loggable);

		private:
			std::string m_Data;
		};

		std::ostream& operator<<(std::ostream& stream, const Loggable& loggable);
	}
}