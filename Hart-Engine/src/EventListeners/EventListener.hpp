/*
* Event Listener Interface
*/

#pragma once

#include "Events/Event.hpp"

namespace Hart {
	namespace EventListeners {
		class EventListener {
		public:
			EventListener() {}
			virtual ~EventListener() {}

			virtual void OnEvent(const Hart::Events::Event& e) = 0;
		};
	}
}