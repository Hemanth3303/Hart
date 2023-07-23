#pragma once

#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "Maths/Vec2.hpp"

namespace Hart {
	namespace Graphics {
		// each sprite in the spritesheet must be of the same size
		// sprites are indexed from left to right, bottom to top
		// ie, sprite at (0, 0) is at bottom left
		class SpriteSheet {
		public:
			// sprite size is the size of one sprite in the spritesheet
			SpriteSheet(const Image& image, const Maths::Vec2& spriteSize, TextureMagFilter magFilter = TextureMagFilter::Linear, TextureMinFilter minFiler = TextureMinFilter::LinearLinear);
			// sprite size is the size of one sprite in the spritesheet
			SpriteSheet(const std::string& filePath, const Maths::Vec2& spriteSize, TextureMagFilter magFilter = TextureMagFilter::Linear, TextureMinFilter minFiler = TextureMinFilter::LinearLinear);
			~SpriteSheet();

			inline std::shared_ptr<Texture2D> getTexture() const { return m_Texture; }
			inline const Maths::Vec2& getSpriteSize() const { return m_SpriteSize; }
			inline const Maths::Vec2& getSpriteSheetSize() const { return m_SpriteSheetSize; }
		private:
			std::shared_ptr<Texture2D> m_Texture;
			Maths::Vec2 m_SpriteSize;
			Maths::Vec2 m_SpriteSheetSize;
		};
	}
}