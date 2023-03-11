#include "HartPch.hpp"
#include "Image.hpp"

#include "stb_image.h"

namespace Hart {
	namespace Graphics {
		Image::Image(const std::string& fileName) {
			if (!Utils::FileManager::FileExists(fileName)) {
				HART_ENGINE_ERROR(std::string("Image File: ") + fileName + std::string(" doesn't exist, is the file path and/or name correct?"));
				return;
			}
			HART_ENGINE_LOG(std::string("Loading Image: ") + fileName);
			stbi_set_flip_vertically_on_load(true);
			m_ImageData = stbi_load(fileName.c_str(), &m_Width, &m_Height, &m_NoOfChannels, 0);
		}

		Image::~Image() {
			stbi_image_free(m_ImageData);
			stbi_set_flip_vertically_on_load(false);
		}
	}
}