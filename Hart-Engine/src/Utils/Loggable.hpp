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
		// Utility class used by the Logger to help log different types, including primitivies and Hart objects
		class Loggable {
		public:
			Loggable(std::int8_t value);
			Loggable(std::int16_t value);
			Loggable(std::int32_t value);
			Loggable(std::int64_t value);

			Loggable(std::uint8_t value);
			Loggable(std::uint16_t value);
			Loggable(std::uint32_t value);
			Loggable(std::uint64_t value);

			Loggable(float value);
			Loggable(double value);

			Loggable(long value);
			Loggable(unsigned long value);

			Loggable(char* value);
			Loggable(const char* value);
			Loggable(unsigned char* value);
			Loggable(const unsigned char* value);
			Loggable(const std::string& value);
			Loggable(std::string_view value);

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