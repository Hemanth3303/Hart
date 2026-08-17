#include "HartPch.hpp"
#include "Layer.hpp"

namespace Hart {

	uint64_t Layer::s_LayerID = 0;

	Layer::Layer()
		: m_Name(std::string("Layer") + std::to_string(s_LayerID++)) {
	}

	Layer::Layer(const std::string& name)
		: m_Name(name) {
		s_LayerID++;
	}

	Layer::~Layer() {
	}
}
