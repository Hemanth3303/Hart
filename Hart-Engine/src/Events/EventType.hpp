#pragma once

namespace Hart {
	namespace Events {
		enum class EventType {
			None = -1,

			WindowResizedEvent,
			WindowClosedEvent,
			WindowMovedEvent,
			WindowFocusGainedEvent,
			WindowFocusLostEvent,

			KeyPressedEvent,
			KeyRepeatEvent,
			KeyReleasedEvent,

			MouseButtonPressedEvent,
			MouseButtonReleasedEvent,
			MouseMovedEvent,
			MouseWheelScrolledEvent,

		};
	}
}