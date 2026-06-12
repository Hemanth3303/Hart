#include "HartPch.hpp"
#include "LayerStack.hpp"

namespace Hart {
	LayerStack::LayerStack() {

	}

	LayerStack::~LayerStack() {
		popAll();
	}

	void LayerStack::pushLayer(const std::shared_ptr<Layer>& layer) {
		if(m_LayerMap.contains(layer->getName()) || m_OverlayMap.contains(layer->getName())) {
			HART_ENGINE_ERROR("A Layer or an Overlay with that name already exists, aborting push");
			HART_DEBUG_BREAK();
		}
		else {
			m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
			m_LayerInsertIndex++;
			m_LayerMap.insert({layer->getName(), layer});
			layer->onAttach();
		}
	}

	void LayerStack::popLayer(const std::shared_ptr<Layer>& layer) {
		auto itr = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (itr != m_Layers.begin() + m_LayerInsertIndex) {
			layer->onDetach();
			m_Layers.erase(itr);
			m_LayerInsertIndex--;
			m_LayerMap.erase(layer->getName());
		}

	}

	void LayerStack::pushOverlay(const std::shared_ptr<Layer>& overlay) {
		if(m_LayerMap.contains(overlay->getName()) || m_OverlayMap.contains(overlay->getName())) {
			HART_ENGINE_ERROR("A Layer or an Overlay with that name already exists, aborting push");
			HART_DEBUG_BREAK();
		}
		else {
			m_Layers.emplace_back(overlay);
			m_OverlayMap.insert({overlay->getName(), overlay});
			overlay->onAttach();
		}
	}

	void LayerStack::popOverlay(const std::shared_ptr<Layer>& overlay) {
		auto itr = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (itr != m_Layers.end()) {
			overlay->onDetach();
			m_Layers.erase(itr);
			m_OverlayMap.erase(overlay->getName());
		}
	}
    void LayerStack::popAll() {
		for (const auto& layer : m_Layers) {
			layer->onDetach();
		}
		m_Layers.clear();
		m_LayerMap.clear();
		m_OverlayMap.clear();
    }

	std::shared_ptr<Layer> LayerStack::getLayer(const std::string& layerName) {
		if(!layerExists(layerName)) {
			HART_ENGINE_ERROR("Layer named " + layerName + " doesn't exist. Returning nullptr");
			return nullptr;
		}
		return m_LayerMap[layerName];
	}
	
	std::shared_ptr<Layer> LayerStack::getOverlay(const std::string& overlayName) {
	if(!overlayExists(overlayName)) {
			HART_ENGINE_ERROR("Overlay named " + overlayName + " doesn't exist. Returning nullptr");
			return nullptr;
		}
		return m_OverlayMap[overlayName];
	}

}