/*
* represents a generic image
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Graphics {
		class Image {
		public:
			Image(const std::string& fileName);
			Image(uint32_t* buffer, int32_t width, int32_t height, int32_t noOfChannels = 4);
			~Image();

			inline const int32_t getWidth() const { return m_Width; }
			inline const int32_t getHeight() const { return m_Height; }
			inline const int32_t getNoOfChannels() const { return m_NoOfChannels; }
			inline const uint32_t* getImageData() const { return m_ImageData; }
		private:
			int32_t m_Width = 0, m_Height = 0, m_NoOfChannels = 0;
			uint32_t* m_ImageData = nullptr;
		};
	}
}
