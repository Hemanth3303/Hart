#pragma once

#include "Events/Event.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace Hart {
	// Base Layer class
	class Layer {
	public:
		Layer();
		Layer(std::string_view name);
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onEvent(Event& e) {}
		virtual void update(const float deltaTime) {}
		virtual void render() {}

		inline std::string_view getName() const { return m_Name; }

	private:
		std::string m_Name;
		// a name is not given, the layer is named as Layer+s_LayerCount
		inline static uint64_t s_LayerCount = 0;
	};
}
