#include "HartPch.hpp"
#include "Core/Assert.hpp"
#include "PlatformTime.hpp"

namespace Hart {
	namespace Platform {
		bool GmTime(const std::time_t& epochSeconds, std::tm& calendarTime) {
#if defined(HART_ENGINE_PLATFORM_WINDOWS)
			auto status = gmtime_s(&calendarTime, &epochSeconds);
			HART_DEBUG_ASSERT(status == 0, "Failed to get gm time");
			return (status == 0);
#else
			auto status = gmtime_r(&epochSeconds, &calendarTime);
			HART_DEBUG_ASSERT(status != nullptr, "Failed to get gm time");
			return (status != nullptr);
#endif
		}

		bool LocalTime(const std::time_t& epochSeconds, std::tm& calendarTime) {
#if defined(HART_ENGINE_PLATFORM_WINDOWS)
			auto status = localtime_s(&calendarTime, &epochSeconds);
			HART_DEBUG_ASSERT(status == 0, "Failed to get local time");
			return (status == 0);
#else
			auto status = localtime_r(&epochSeconds, &calendarTime);
			HART_DEBUG_ASSERT(status != nullptr, "Failed to get local time");
			return (status != nullptr);
#endif
		}
	}
}
