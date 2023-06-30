/*
* OpenGL Textures
*/

#pragma once

#include "HartPch.hpp"
#include "Image.hpp"

namespace Hart {
	namespace Graphics {
		enum class TextureMagFilter {
			Unknown = -1,
			Nearest = 0x2600,
			Linear = 0x2601,
		};

		enum class TextureMinFilter {
			Unknown = -1,
			NearestNearest = 0x2700,
			LinearNearest = 0x2701,
			NearestLinear = 0x2702,
			LinearLinear = 0x2703,
		};

		enum class TextureRepeatFilter {
			Unknown = -1,
			Repeat = 0x2901,
			MirroredRepeat = 0x8370,
			ClampToEdge = 0x812F,
			ClampToBorder = 0x812D,
		};

		// OpenGL Textures
		class Texture2D {
		public:
			Texture2D(const Image& image, TextureMagFilter magFilter = TextureMagFilter::Linear, TextureMinFilter minFiler = TextureMinFilter::LinearLinear, TextureRepeatFilter repeatX = TextureRepeatFilter::Repeat, TextureRepeatFilter repeatY = TextureRepeatFilter::Repeat);
			Texture2D(const std::string& filePath, TextureMagFilter magFilter = TextureMagFilter::Linear, TextureMinFilter minFiler = TextureMinFilter::LinearLinear, TextureRepeatFilter repeatX = TextureRepeatFilter::Repeat, TextureRepeatFilter repeatY = TextureRepeatFilter::Repeat);
			Texture2D(std::uint32_t* buffer, std::uint32_t width, std::uint32_t height, std::uint32_t channels = 4, TextureMagFilter magFilter = TextureMagFilter::Linear, TextureMinFilter minFiler = TextureMinFilter::LinearLinear, TextureRepeatFilter repeatX = TextureRepeatFilter::Repeat, TextureRepeatFilter repeatY = TextureRepeatFilter::Repeat);
			~Texture2D();

			void bind(std::uint32_t slot = 0) const;
			void unbind(std::uint32_t slot = 0) const;

			inline const Image& getImage() const { return m_Image; }
			inline const std::uint32_t getWidth() const { return m_Image.getWidth(); }
			inline const std::uint32_t getHeight() const { return m_Image.getHeight(); }
			inline const std::int32_t getSlot() const { return m_Slot; }
		private:
			void init(TextureMagFilter magFilter, TextureMinFilter minFilter, TextureRepeatFilter repeatX, TextureRepeatFilter repeatY);
		private:
			std::uint32_t m_TextureID = 0;
			Image m_Image;
			mutable std::int32_t m_Slot = -1;
		};
	}
}