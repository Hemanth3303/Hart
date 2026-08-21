#pragma once

namespace Hart {
	enum class EventType {
		None = -1,

		WindowResizedEvent,
		WindowClosedEvent,
		WindowMovedEvent,
		WindowFocusGainedEvent,
		WindowFocusLostEvent,
		WindowMinimizedEvent,
		WindowRestoredFromMinimizedEvent,
		WindowMaximizedEvent,
		WindowRestoredFromMaximizedEvent,

		KeyPressedEvent,
		KeyRepeatEvent,
		KeyReleasedEvent,

		MouseButtonPressedEvent,
		MouseButtonReleasedEvent,
		MouseMovedEvent,
		MouseWheelScrolledEvent,

	};
}
