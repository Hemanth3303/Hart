#pragma once

namespace Hart {
	namespace Events {
		enum class EventType {
			None = -1,

			WindowResized,
			WindowClosed,
			WindowMoved,
			WindowFocusGained,
			WindowFocusLost,

			KeyPressed,
			KeyRepeat,
			KeyReleased,

			MouseButtonPressed,
			MouseButtonReleased,
			MouseMoved,
			MouseWheelScrolled,

		};
	}
}