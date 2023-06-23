/*
* OpenGL Textures
*/

#pragma once

#include "HartPch.hpp"
#include "Image.hpp"

namespace Hart {
	namespace Graphics {
		enum class MagFilter {
			Unknown = -1,
			Nearest = 0x2600,
			Linear = 0x2601,
		};

		enum class MinFilter {
			Unknown = -1,
			NearestNearest = 0x2700,
			LinearNearest = 0x2701,
			NearestLinear = 0x2702,
			LinearLinear = 0x2703,
		};
		
		// OpenGL Textures
		class Texture2D {
		public:
			Texture2D(const Image& image, MagFilter magFilter = MagFilter::Linear, MinFilter minFiler = MinFilter::LinearLinear);
			Texture2D(const std::string& filePath, MagFilter magFilter = MagFilter::Linear, MinFilter minFiler = MinFilter::LinearLinear);
			Texture2D(std::uint32_t* buffer, std::uint32_t width, std::uint32_t height, std::uint32_t channels = 4, MagFilter magFilter = MagFilter::Linear, MinFilter minFiler = MinFilter::LinearLinear);
			~Texture2D();

			void bind(std::uint32_t slot = 0) const;
			void unbind(std::uint32_t slot = 0) const;

			inline const Image& getImage() const { return m_Image; }
			inline const std::uint32_t getWidth() const { return m_Image.getWidth(); }
			inline const std::uint32_t getHeight() const { return m_Image.getHeight(); }
			inline const std::int32_t getSlot() const { return m_Slot; }
		private:
			void init(MagFilter magFilter, MinFilter minFilter);
		private:
			std::uint32_t m_TextureID = 0;
			Image m_Image;
			mutable std::int32_t m_Slot = -1;
		};
	}
}