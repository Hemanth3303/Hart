#include "HartPch.hpp"
#include "SpriteSheet.hpp"

namespace Hart {
	SpriteSheet::SpriteSheet(const std::string& filePath, const Vec2& spriteSize, const Texture2DSpecification& texture2DSpecs)
		: m_SpriteSize(spriteSize) {

		bool fileExists = FileManager::FileExists(filePath);
		HART_DEBUG_ASSERT(fileExists, "Reason: The spritesheet file \"", filePath, "\" not found. ", "Is the name and/or path correct?");
		if (!fileExists) {
			HART_ENGINE_ERROR(LogSource::EngineGraphics, "The spritesheet file \"", filePath, "\" not found. ", "Is the name and/or path correct?");
			return;
		}

		m_Texture = std::make_shared<Texture2D>(filePath, texture2DSpecs);
		m_SpriteSheetSize.x = static_cast<float>(m_Texture->getWidth());
		m_SpriteSheetSize.y = static_cast<float>(m_Texture->getHeight());
	}

	SpriteSheet::~SpriteSheet() {
	}
}
