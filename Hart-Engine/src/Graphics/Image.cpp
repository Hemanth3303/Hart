#include "HartPch.hpp"
#include "Image.hpp"

#include "stb_image.h"

namespace Hart {
	namespace Graphics {
		Image::Image(const std::string& fileName)
			: m_WasCreatedFromCharBuff(false) {
			if (!Utils::FileManager::FileExists(fileName)) {
				HART_ENGINE_ERROR(std::string("Image File: ") + fileName + std::string(" doesn't exist, is the file path and/or name correct?"));
				return;
			}
			HART_ENGINE_LOG(std::string("Loading Image: ") + fileName);
			stbi_set_flip_vertically_on_load(true);
			m_ImageData = reinterpret_cast<uint32_t*>(stbi_load(fileName.c_str(), &m_Width, &m_Height, &m_NoOfChannels, STBI_rgb_alpha));
			stbi_set_flip_vertically_on_load(false);
		}

        Image::Image(uint32_t* dataBuffer, int32_t width, int32_t height, int32_t noOfChannels)
			: m_ImageData(dataBuffer), m_Width(width), m_Height(height), m_NoOfChannels(noOfChannels), m_WasCreatedFromCharBuff(true) {

        }

		Image::~Image() {
			if (!m_WasCreatedFromCharBuff) {
				stbi_image_free(m_ImageData);
			}
		}
	}
}