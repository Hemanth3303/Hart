/*
* Not sure how i want to make this class work, honestly.
* TODO: Change this probably to better working stuff
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	class Engine {
	public:
		Engine() = delete;
		Engine(const Engine&) = delete;

		static void Init();
		static void DeInit();
		static void Update();

		static const bool& Running();

	private:
		static bool m_IsRunning;
	};
}