/*
 * Note: Learned most of this stuff from TheCherno's game engine series
 */

#pragma once

#include "EventType.hpp"
#include "EventCategory.hpp"

#include <iostream>
#include <string_view>

#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace Hart {
	class EventDispatcher;
	// Base class for events
	class Event {
	public:
		Event() = default;
		virtual ~Event() = default;

		virtual EventType getEventType() const = 0;
		virtual std::string_view getName() const = 0;
		virtual int32_t getEventCategoryFlags() const = 0;
		virtual std::string toString() const { return std::string(getName()); }

		inline bool isInCategory(EventCategory category) const { return getEventCategoryFlags() & category; }
		inline bool getHandled() const { return m_Handled; }

	private:
		bool m_Handled = false;

		friend class Hart::EventDispatcher;
	};

	inline std::ostream& operator<<(std::ostream& stream, const Event& e) {
		stream << e.toString();
		return stream;
	}
}
