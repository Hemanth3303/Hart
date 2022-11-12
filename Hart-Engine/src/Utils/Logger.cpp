#include "HartPch.hpp"
#include "Logger.hpp"

namespace Hart {
	namespace Utils {
		void Logger::LogMessage(const Loggable& message, const LogSeverity& logSeverity) {
			std::cout << message << "\n";
		}
	}
}