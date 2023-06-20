#include "HartPch.hpp"
#include "Image.hpp"
#include "stb_image.h"

namespace Hart {
	namespace Graphics {
		Image::Image(std::uint32_t* buffer, std::int32_t width, std::int32_t height, std::int32_t channels)
			: m_Buffer(buffer), m_Width(width), m_Height(height), m_Channels(channels), m_loadedFromStbi(false) {

		}

		Image::Image(const std::string& filePath)
			: m_loadedFromStbi(true) {
			if (!Utils::FileManager::FileExists(filePath)) {
				HART_ENGINE_ERROR("File " + filePath + "does not exits", "Is the name and/or path correct?");
				HART_ASSERT(false);
			}
			else {
				m_Buffer = reinterpret_cast<std::uint32_t*>(stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_Channels, 0));
			}
		}

		Image::~Image() {
			if (m_loadedFromStbi) {
				stbi_image_free(m_Buffer);
			}
		}
	}
}