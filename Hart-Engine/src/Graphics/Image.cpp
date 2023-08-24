#include "HartPch.hpp"
#include "Image.hpp"
#include "stb_image.h"

namespace Hart {
	Image::Image(std::uint32_t* buffer, std::uint32_t width, std::uint32_t height, std::uint32_t channels)
		: m_Buffer(buffer), m_Width(width), m_Height(height), m_Channels(channels), m_loadedFromStbi(false) {

	}

	Image::Image(const std::string& filePath)
		: m_loadedFromStbi(true) {
		if (!FileManager::FileExists(filePath)) {
			HART_ENGINE_ERROR("File " + filePath + " does not exits", "Is the name and/or path correct?");
		}
		else {
			int32_t width, height, channels;

			stbi_set_flip_vertically_on_load(true);
			m_Buffer = reinterpret_cast<std::uint32_t*>(stbi_load(filePath.c_str(), &width, &height, &channels, 0));
			stbi_set_flip_vertically_on_load(false);

			m_Width = width;
			m_Height = height;
			m_Channels = channels;
		}
	}

	Image::~Image() {
		if (m_loadedFromStbi) {
			stbi_image_free(m_Buffer);
		}
	}
}