#pragma once

#include <cstdio>

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