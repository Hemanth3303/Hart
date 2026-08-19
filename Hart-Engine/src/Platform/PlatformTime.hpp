#pragma once

#include <ctime>

namespace Hart {
	namespace Platform {
		// modifies calendarTime
		bool GmTime(const std::time_t& epochSeconds, std::tm& calendarTime);
		// modifies calendarTime
		bool LocalTime(const std::time_t& epochSeconds, std::tm& calendarTime);
	}
}
