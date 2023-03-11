/*
* Class Representing a 2d texture for opengl
*/

#pragma once

#include "HartPch.hpp"
#include "Image.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		class Texture2D {
		public:
			// defaults: magFilterParam = GL_LINEAR, minFliterParam = GL_LINEAR_MIPMAP_LINEAR;
			Texture2D(const std::string& fileName, GLint magFilterParam = GL_LINEAR, GLint minFliterParam = GL_LINEAR_MIPMAP_LINEAR);
			~Texture2D();

			void bind() const;
			void unbind() const;

			inline const Image& getImage() const { return m_Image; }
			inline const int32_t getTextureSlot() const { return m_TextureSlot; }
		private:
			uint32_t m_ID = 0;
			int32_t m_TextureSlot = -1;
			Image m_Image;
			static int32_t s_NoOfTextures;
		};
	}
}