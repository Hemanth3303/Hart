#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace Hart {
	class ScopedTimer {
	public:
		ScopedTimer(std::string_view name);
		~ScopedTimer();

	private:
		std::string m_Name;
		uint64_t m_StartTime;
	};
}
