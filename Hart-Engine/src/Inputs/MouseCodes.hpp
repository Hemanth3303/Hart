#pragma once

namespace Hart {
	namespace Inputs {
		// These follow the same numberings as GLFW mousecodes
		enum class MouseCode {
			Unknown = -1,
			One = 0,
			Two = 1,
			Three = 2,
			Four = 3,
			Five = 4,
			Six = 5,
			Seven = 6,
			Eight = 7,

			Last = Eight,
			Left = One,
			Right = Two,
			Middle = Three,
		};
	}
}