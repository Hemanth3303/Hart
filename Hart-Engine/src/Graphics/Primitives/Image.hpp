#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Graphics {
		class Image {
		public:
		public:
			// does not take ownership of the provided buffer
			Image(std::uint32_t* buffer, std::int32_t width, std::int32_t height, std::int32_t channels = 4);
			Image(const std::string& filePath);
			~Image();

			inline const std::int32_t getWidth() const { return m_Width; }
			inline const std::int32_t getHeight() const { return m_Height; }
			inline const std::int32_t getChannels() const { return m_Channels; }
			inline const std::uint32_t* const& getBuffer() const { return m_Buffer; }

			inline void setBuffer(std::uint32_t* buffer) { m_Buffer = buffer; }
		private:
			std::uint32_t* m_Buffer = nullptr;
			std::int32_t m_Width = -1, m_Height = -1;
			std::int32_t m_Channels = -1;

			bool m_loadedFromStbi = false;
		};
	}
}