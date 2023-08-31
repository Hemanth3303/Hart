#pragma once

#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	// each sprite in the spritesheet must be of the same size
	// sprites are indexed from left to right, top to bottom
	// ie, sprite at (0, 0) is at top left
	class SpriteSheet {
	public:
		// sprite size is the size of one sprite in the spritesheet
		SpriteSheet(const Image& image, const Vec2& spriteSize, const Texture2DSpecification& texture2DSpecs = {});
		// sprite size is the size of one sprite in the spritesheet
		SpriteSheet(const std::string& filePath, const Vec2& spriteSize, const Texture2DSpecification& texture2DSpecs = {});
		~SpriteSheet();

		inline std::shared_ptr<Texture2D> getTexture() const { return m_Texture; }
		inline const Vec2& getSpriteSize() const { return m_SpriteSize; }
		inline const Vec2& getSpriteSheetSize() const { return m_SpriteSheetSize; }
	private:
		std::shared_ptr<Texture2D> m_Texture;
		Vec2 m_SpriteSize;
		Vec2 m_SpriteSheetSize;
	};
}