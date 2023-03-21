#pragma once

#include "HartPch.hpp"
#include "Image.hpp"

#include "glad/glad.h"

#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_LINEAR_MIPMAP_LINEAR 0x2703

namespace Hart {
	namespace Graphics {
		enum class MagFilterParams {
			None = -1,
			GLNearest = GL_NEAREST,
			GLLinear = GL_LINEAR,
		};
		enum class MinFilterParams {
			GLNearestMipMapNearest = GL_NEAREST_MIPMAP_NEAREST,
			GLLinearMipMapNearest = GL_LINEAR_MIPMAP_NEAREST,
			GLNearestMipMapLinear = GL_NEAREST_MIPMAP_LINEAR,
			GLLinearMipMapLinear = GL_LINEAR_MIPMAP_LINEAR,
		};
		// Class Representing a 2d texture for OpenGL
		class Texture2D {
		public:
			// defaults: magFilterParam = GL_LINEAR, minFliterParam = GL_LINEAR_MIPMAP_LINEAR;
			Texture2D(const std::string& fileName, MagFilterParams magFilterParam = MagFilterParams::GLLinear, MinFilterParams minFliterParam = MinFilterParams::GLLinearMipMapLinear);
			Texture2D(const Image& image, MagFilterParams magFilterParam = MagFilterParams::GLLinear, MinFilterParams minFliterParam = MinFilterParams::GLLinearMipMapLinear);
			Texture2D(uint32_t* dataBuffer, int32_t width, int32_t height, int32_t noOfChannels = 4, MagFilterParams magFilterParam = MagFilterParams::GLLinear, MinFilterParams minFliterParam = MinFilterParams::GLLinearMipMapLinear);
			~Texture2D();

			void bind() const;
			void unbind() const;

			inline const Image& getImage() const { return m_Image; }
			inline const int32_t getTextureSlot() const { return m_TextureSlot; }
		private:
			void init(MagFilterParams magFilterParam, MinFilterParams minFliterParam);
		private:
			uint32_t m_ID = 0;
			int32_t m_TextureSlot = -1;
			Image m_Image;
			static int32_t s_NoOfTextures;
		};
	}
}