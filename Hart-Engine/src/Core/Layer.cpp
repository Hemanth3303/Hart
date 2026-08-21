#include "HartPch.hpp"
#include "Layer.hpp"

namespace Hart {
	Layer::Layer()
		: m_Name(std::string("Layer") + std::to_string(s_LayerCount++)) {
	}

	Layer::Layer(std::string_view name)
		: m_Name(name) {
		s_LayerCount++;
	}

	Layer::~Layer() {
	}
}
