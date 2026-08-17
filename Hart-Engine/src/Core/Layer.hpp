#pragma once

#include "Events/Event.hpp"

#include <cstdint>

namespace Hart {
	// Base Layer class
	class Layer {
	public:
		Layer();
		Layer(const std::string& name);
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onEvent(Event& e) {}
		virtual void update(const float deltaTime) {}
		virtual void render() {}

		inline const std::string& getName() const { return m_Name; }

	private:
		std::string m_Name;
		static uint64_t s_LayerID;
	};
}
