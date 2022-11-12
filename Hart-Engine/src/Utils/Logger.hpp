#pragma once

#include "HartPch.hpp"
#include "Loggable.hpp"

namespace Hart {
	namespace Utils {

		enum class LogSeverity {
			TRACE = 0,
			INFO,
			WARNING,
			ERROR,
			FATAL,
		};

		class Logger {
		public:
			static void LogMessage(const Loggable& message, const LogSeverity& logSeverity);
		};
	}
}