#pragma once

namespace Hart {
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