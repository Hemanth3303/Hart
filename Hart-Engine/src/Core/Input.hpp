#pragma once

#include "HartPch.hpp"

namespace Hart {
	//Based on the GLFW_KEY definitions
	namespace KeyBoard {
		enum class Key {
			InvalidKey = -1,

			//printable keys
			Space = 32,
			Apostrophe = 39,
			Comma = 44,
			Minus = 45,
			Period = 46,
			Slash = 47,
			Key0 = 48,
			Key1 = 49,
			Key2 = 50,
			Key3 = 51,
			Key4 = 52,
			Key5 = 53,
			Key6 = 54,
			Key7 = 55,
			Key8 = 56,
			Key9 = 57,
			SemiColon = 59,
			Equal = 61,
			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,
			BackSlash = 92,
			RightBracket = 93,
			GraveAccent = 96,

			KeyWorld1 = 161,
			KeyWorld2 = 162,

			//Function keys
			Escape = 256,
			Enter = 257,
			Tab = 258,
			BackSpace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,
			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			Numpad0 = 320,
			Numpad1 = 321,
			Numpad2 = 322,
			Numpad3 = 323,
			Numpad4 = 324,
			Numpad5 = 325,
			Numpad6 = 326,
			Numpad7 = 327,
			Numpad8 = 328,
			Numpad9 = 329,
			NumpadDecimal = 330,
			NumpadDivide = 331,
			NumpadMultiply = 332,
			NumpadSubstract = 333,
			NumpadAdd = 334,
			NumpadEnter = 335,
			NumpadEqual = 336,
			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348,
		};
		bool isKeyPressed(Key key);
		bool isKeyReleased(Key key);
	}

	namespace Mouse {
		enum class Button {
			Button1 = 0,
			Button2 = 1,
			Button3 = 2,
			Button4 = 3,
			Button5 = 4,
			Button6 = 5,
			Button7 = 6,
			Button8 = 7,
			ButtonLeft = Button1,
			ButtonRight = Button2,
			ButtonMiddle = Button3,
		};
		bool isButtonPressed(Button button);
		bool isButtonReleased(Button button);
	}

	namespace JoyStick {
		enum class Button {
			A = 0,
			B = 1,
			X = 2,
			Y = 3,
			LeftBumper = 4,
			RightBumper = 5,
			Back = 6,
			Start = 7,
			Guide = 8,
			LeftThumb = 9,
			RightThumb = 10,
			DPadUp = 11,
			DPadRight = 12,
			DPadDown = 13,
			DPadLeft = 14,

			Cross = A,
			Circle = B,
			Square = X,
			Triangle = Y,
		};

		enum class Axis {
			LeftX = 0,
			LeftY = 1,
			RightX = 2,
			RightY = 3,
			LeftTrigger = 4,
			RightTrigger = 5,
		};
		
		//not implemented yet
		bool isButtonPressed(Button button);
		//not implemented yet
		bool isButtonReleased(Button button);
	}
}