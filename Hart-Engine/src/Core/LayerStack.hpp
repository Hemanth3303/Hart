#pragma once

#include "HartPch.hpp"
#include "Layer.hpp"

namespace Hart {
	// LayerStack
	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(const std::shared_ptr<Layer>& layer);
		void popLayer(const std::shared_ptr<Layer>& layer);
		void pushOverlay(const std::shared_ptr<Layer>& overlay);
		void popOverlay(const std::shared_ptr<Layer>& overlay);

		// Deletes all layers and overlays
		void popAll();

		std::shared_ptr<Layer> getLayer(const std::string& layerName);
		std::shared_ptr<Layer> getOverlay(const std::string& overlayName);

		inline bool layerExists(const std::string& layerName) { return m_LayerMap.contains(layerName); }
		inline bool overlayExists(const std::string& overlayName) { return m_OverlayMap.contains(overlayName); }

		std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<std::shared_ptr<Layer>>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<std::shared_ptr<Layer>>::const_iterator end() const { return m_Layers.end(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		std::vector<std::shared_ptr<Layer>> m_Layers;
		std::unordered_map<std::string, std::shared_ptr<Layer>> m_LayerMap;
		std::unordered_map<std::string, std::shared_ptr<Layer>> m_OverlayMap;
		std::uint32_t m_LayerInsertIndex = 0;
	};
}
