#include "HartPch.hpp"
#include "Loggable.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"

namespace Hart {
	Loggable::Loggable(char value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(short value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(int value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(long value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(long long value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(unsigned char value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(unsigned short value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(unsigned int value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(unsigned long value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(unsigned long long value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(float value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(double value) {
		m_Data = std::to_string(value);
	}

	Loggable::Loggable(long double value) {
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


	Loggable::Loggable(const Vec2& vec) {
		m_Data = vec.toString();
	}

	Loggable::Loggable(const Vec3& vec) {
		m_Data = vec.toString();
	}

	Loggable::Loggable(const Vec4& vec) {
		m_Data = vec.toString();
	}

	Loggable::Loggable(const Mat4& matrix) {
		m_Data = matrix.toString();
	}

	Loggable::Loggable(const Event& e) {
		m_Data = e.toString();
	}

	Loggable::~Loggable() {

	}

	std::ostream& operator<<(std::ostream& stream, const Loggable& loggable) {
		stream << loggable.m_Data;
		return stream;
	}
}