/*
* Base class for events
* Note: Learned most of this stuff from TheCherno's game engine series
*/

#pragma once

#include "HartPch.hpp"
#include "EventType.hpp"
#include "EventCategory.hpp"

namespace Hart {
	namespace Events {
		class Event {
		public:
			Event() = default;
			virtual ~Event() = default;

			virtual EventType getEventType() const = 0;
			virtual std::string_view getName() const = 0;
			virtual int32_t getEventCategoryFlags() const = 0;
			virtual std::string toString() const { return std::string(getName()); }

			bool isInCategory(EventCategory category) {
				return getEventCategoryFlags() & category;
			}

		public:
			bool m_Handled = false;
		};

		inline std::ostream& operator<<(std::ostream& stream, const Event& e) {
			stream << e.toString();
			return stream;
		}

	}
}