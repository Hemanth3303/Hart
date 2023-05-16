/*
* Note: Learned most of this stuff from TheCherno's game engine series
*/


#pragma once

#include "HartPch.hpp"
#include "EventType.hpp"
#include "EventCategory.hpp"

#define BIND_EVENT_FUNC(x) std::bind (&x, this, std::placeholders::_1)

namespace Hart {
	namespace Events {
		// Base class for events
		class Event {
		public:
			Event() = default;
			virtual ~Event() = default;

			virtual EventType getEventType() const = 0;
			virtual std::string_view getName() const = 0;
			virtual std::int32_t getEventCategoryFlags() const = 0;
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