#include "HartPch.hpp"
#include "SpriteSheet.hpp"

namespace Hart {
	SpriteSheet::SpriteSheet(const Image& image, const Vec2& spriteSize, const Texture2DSpecification& texture2DSpecs)
		: m_SpriteSize(spriteSize) {

		m_Texture = std::make_shared<Texture2D>(image, texture2DSpecs);
		m_SpriteSheetSize.x = static_cast<float>(m_Texture->getWidth());
		m_SpriteSheetSize.y = static_cast<float>(m_Texture->getHeight());
	}

	SpriteSheet::SpriteSheet(const std::string& filePath, const Vec2& spriteSize, const Texture2DSpecification& texture2DSpecs)
		: m_SpriteSize(spriteSize) {
		m_Texture = std::make_shared<Texture2D>(filePath, texture2DSpecs);
		m_SpriteSheetSize.x = static_cast<float>(m_Texture->getWidth());
		m_SpriteSheetSize.y = static_cast<float>(m_Texture->getHeight());
	}

	SpriteSheet::~SpriteSheet() {

	}
}