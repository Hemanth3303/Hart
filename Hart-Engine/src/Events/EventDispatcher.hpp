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

			// if the event type of the template and m_Event are same, then 'func' gets called
			template<typename T>
			bool dispatch(EventFunction<T&> func) {
				if (m_Event.getEventType() == T::GetStaticType()) {
					// get address of m_Event
					// convert pointer of derived(from event class) to base class pointer(event class)
					// dereference the pointer
					//m_Event.m_Handled = func(*(T*)&(m_Event));
					m_Event.m_Handled = func(*(static_cast<T*>(&m_Event)));
					return true;
				}
				return false;
			}

		private:
			Event& m_Event;
		};
	}
}