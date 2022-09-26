#pragma once

#include "HartPch.hpp"

namespace Hart {
	class Scene {
	public:
		Scene();
		virtual ~Scene();

		void handleEvents();
		void update();

	private:
		std::string m_Name;
		friend class Engine;
	};
}