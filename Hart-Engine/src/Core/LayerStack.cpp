#include "HartPch.hpp"
#include "LayerStack.hpp"

namespace Hart {
	LayerStack::LayerStack() {

	}

	LayerStack::~LayerStack() {
		popAll();
	}

	void LayerStack::pushLayer(const std::shared_ptr<Layer>& layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->onAttach();
	}

	void LayerStack::popLayer(const std::shared_ptr<Layer>& layer) {
		auto itr = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (itr != m_Layers.begin() + m_LayerInsertIndex) {
			layer->onDetach();
			m_Layers.erase(itr);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::pushOverlay(const std::shared_ptr<Layer>& overlay) {
		m_Layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void LayerStack::popOverlay(const std::shared_ptr<Layer>& overlay) {
		auto itr = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (itr != m_Layers.end()) {
			overlay->onDetach();
			m_Layers.erase(itr);
		}
	}
    void LayerStack::popAll() {
		for (const auto& layer : m_Layers) {
			layer->onDetach();
		}
		m_Layers.clear();
    }
}