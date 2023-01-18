#pragma once

#include "Event.hpp"

namespace Hart {
	namespace Events {
		class EventDispatcher {
		public:
			EventDispatcher(Event& event)
				: m_Event(event) {

			}

			template<typename T, typename F>
			bool dispatch(const F& func) {
				if (m_Event.getEventType() == T::GetStaticType()) {
					m_Event.m_Handled |= func(static_cast<T&>(m_Event));
					return true;
				}
				return false;
			}

		private:
			Event& m_Event;
		};
	}
}