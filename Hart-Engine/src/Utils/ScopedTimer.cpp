#include "HartPch.hpp"
#include "ScopedTimer.hpp"
#include "Timer.hpp"
#include "Logger.hpp"

namespace Hart {
	ScopedTimer::ScopedTimer(std::string_view name) : m_Name(name) {
		m_StartTime = Timer::GetTimepointNanoseconds();
	}

	ScopedTimer::~ScopedTimer() {
		uint64_t endTime = Timer::GetTimepointNanoseconds();
		uint64_t delta = endTime - m_StartTime;

		HART_ENGINE_INFO("ScopedTimer(", m_Name, "): ", delta, "ns");
	}
}
