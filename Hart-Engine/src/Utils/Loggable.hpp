#pragma once

#include "HartPch.hpp"
#include "Events/Event.hpp"

namespace Hart {
	struct Vec2;
	struct Vec3;
	struct Vec4;
	struct Mat4;

	// Utility class used by the Logger to help log different types, including primitivies and Hart objects
	class Loggable {
	public:
		Loggable(char value);
		Loggable(short value);
		Loggable(int value);
		Loggable(long value);
		Loggable(long long value);

		Loggable(unsigned char value);
		Loggable(unsigned short value);
		Loggable(unsigned int value);
		Loggable(unsigned long value);
		Loggable(unsigned long long value);

		Loggable(float value);
		Loggable(double value);
		Loggable(long double value);

		Loggable(char* value);
		Loggable(const char* value);
		Loggable(unsigned char* value);
		Loggable(const unsigned char* value);
		Loggable(const std::string& value);
		Loggable(std::string_view value);

		Loggable(const Vec2& vec);
		Loggable(const Vec3& vec);
		Loggable(const Vec4& vec);

		Loggable(const Mat4& matrix);
		Loggable(const Event& e);

		~Loggable();

		friend std::ostream& operator<<(std::ostream& stream, const Loggable& loggable);

	private:
		std::string m_Data;
	};

	std::ostream& operator<<(std::ostream& stream, const Loggable& loggable);
}