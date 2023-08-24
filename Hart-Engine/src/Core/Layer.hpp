#pragma once

#include "HartPch.hpp"
#include "Events/Event.hpp"

namespace Hart {
	// Base Layer class
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onEvent(Event& e) {}
		virtual void update(const float deltaTime) {}
		virtual void render() {}

		inline const std::string& getName() const { return m_Name; }
	private:
		std::string m_Name;
	};
}