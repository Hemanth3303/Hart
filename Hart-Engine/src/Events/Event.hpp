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
		class EventDispatcher;
		// Base class for events
		class Event {
		public:
			Event() = default;
			virtual ~Event() = default;

			virtual EventType getEventType() const = 0;
			virtual std::string_view getName() const = 0;
			virtual std::int32_t getEventCategoryFlags() const = 0;
			virtual std::string toString() const { return std::string(getName()); }

			inline const bool isInCategory(EventCategory category) { return getEventCategoryFlags() & category; }
			inline const bool getHandled() const { return m_Handled; }

		private:
			bool m_Handled = false;

			friend class Hart::Events::EventDispatcher;
		};

		inline std::ostream& operator<<(std::ostream& stream, const Event& e) {
			stream << e.toString();
			return stream;
		}

	}
}