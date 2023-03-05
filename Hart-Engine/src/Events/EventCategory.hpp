#pragma once

#define BIT(x) (1 << x)

namespace Hart {
	namespace Events {
		enum EventCategory {
			None = -1,

			WindowEvent = BIT(0),
			InputEvent = BIT(1),
			KeyboardEvent = BIT(2),
			MouseEvent = BIT(3),
			MouseButtonEvent = BIT(4),
		};
	}
}