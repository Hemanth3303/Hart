#include "HartPch.hpp"
#include "SpriteSheet.hpp"

namespace Hart {
	namespace Graphics {
		SpriteSheet::SpriteSheet(const Image& image, const Maths::Vec2& spriteSize, TextureMagFilter magFilter, TextureMinFilter minFiler) 
			:m_SpriteSize(spriteSize) {

			m_Texture = std::make_shared<Texture2D>(image, magFilter, minFiler, TextureRepeatFilter::Repeat, TextureRepeatFilter::Repeat);
			m_SpriteSheetSize.x = static_cast<float>(m_Texture->getWidth());
			m_SpriteSheetSize.y = static_cast<float>(m_Texture->getHeight());
		}

		SpriteSheet::SpriteSheet(const std::string& filePath, const Maths::Vec2& spriteSize, TextureMagFilter magFilter, TextureMinFilter minFiler) 
			: m_SpriteSize(spriteSize) {
			m_Texture = std::make_shared<Texture2D>(filePath, magFilter, minFiler, TextureRepeatFilter::Repeat, TextureRepeatFilter::Repeat);
			m_SpriteSheetSize.x = static_cast<float>(m_Texture->getWidth());
			m_SpriteSheetSize.y = static_cast<float>(m_Texture->getHeight());
		}

		SpriteSheet::~SpriteSheet() {

		}
	}
}