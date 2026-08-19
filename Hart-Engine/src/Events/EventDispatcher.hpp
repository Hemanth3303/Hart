#pragma once

#include "Event.hpp"

#include <concepts>
#include <type_traits>
#include <functional>

namespace Hart {
	template <typename F, typename T>
	concept EventHandler =
		std::invocable<F, T&> &&
		std::same_as<std::invoke_result_t<F, T&>, bool>;

	class EventDispatcher {
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {
		}

		// if the event type of the template and m_Event are same,
		// func is called on m_Event
		template <typename T, typename F>
		requires EventHandler<F, T>
		void dispatch(F&& func) {
			if (m_Event.getEventType() == T::GetStaticType()) {
				m_Event.m_Handled = std::invoke(
					std::forward<F>(func),
					static_cast<T&>(m_Event));
			}
		}

	private:
		Event& m_Event;
	};
}
