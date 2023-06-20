#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Graphics {
		// Abstract Image class
		class Image {
		public:
		public:
			// does not take ownership of the provided buffer
			Image(std::uint32_t* buffer, std::uint32_t width, std::uint32_t height, std::uint32_t channels = 4);
			Image(const std::string& filePath);
			~Image();

			inline const std::uint32_t getWidth() const { return m_Width; }
			inline const std::uint32_t getHeight() const { return m_Height; }
			inline const std::uint32_t getChannels() const { return m_Channels; }
			inline const std::uint32_t* getBuffer() const { return m_Buffer; }

			inline void setBuffer(std::uint32_t* buffer) { m_Buffer = buffer; }
		private:
			std::uint32_t* m_Buffer = nullptr;
			std::uint32_t m_Width = -1, m_Height = -1;
			std::uint32_t m_Channels = -1;

			bool m_loadedFromStbi = false;
		};
	}
}