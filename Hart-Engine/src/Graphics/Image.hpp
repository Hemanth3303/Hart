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
			~Image();

			inline const int32_t getWidth() const { return m_Width; }
			inline const int32_t getHeight() const { return m_Height; }
			inline const int32_t getNoOfChannels() const { return m_NoOfChannels; }
			inline const unsigned char* getImageData() const { return m_ImageData; }
		private:
			int32_t m_Width = 0, m_Height = 0, m_NoOfChannels = 0;
			unsigned char* m_ImageData = nullptr;
		};
	}
}
