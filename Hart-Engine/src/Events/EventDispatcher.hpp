#pragma once

#include "Event.hpp"

namespace Hart {
	namespace Events {
		class EventDispatcher {
			template<typename T>
			using EventFunction = std::function<bool(T&)>;
		public:
			EventDispatcher(Event& event)
				: m_Event(event) {

			}

			template<typename T>
			bool dispatch(EventFunction<T&> func) {
				if (m_Event.getEventType() == T::GetStaticType()) {
					m_Event.m_Handled = func(*(T*)&(m_Event));
					return true;
				}
				return false;
			}

		private:
			Event& m_Event;
		};
	}
}