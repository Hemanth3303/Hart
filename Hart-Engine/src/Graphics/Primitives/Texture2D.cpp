#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "glad/glad.h"

namespace Hart {
	namespace Graphics {
		Texture2D::Texture2D(const Image& image, MagFilter magFilter, MinFilter minFiler) 
			: m_Image(image) {
			
			init(magFilter, minFiler);
		}

		Texture2D::Texture2D(const std::string& filePath, MagFilter magFilter, MinFilter minFiler)
			: m_Image(filePath) {
			
			init(magFilter, minFiler);
		}

		Texture2D::Texture2D(std::uint32_t* buffer, std::uint32_t width, std::uint32_t height, std::uint32_t channels, MagFilter magFilter, MinFilter minFiler) 
			:m_Image(buffer, width, height, channels) {
		
			init(magFilter, minFiler);
		}

		Texture2D::~Texture2D() {
			glDeleteTextures(1, &m_TextureID);
		}

		void Texture2D::bind(std::uint32_t slot) const {
			glBindTextureUnit(slot, m_TextureID);
			m_Slot = slot;
		}

		void Texture2D::unbind(std::uint32_t slot) const {
			glBindTextureUnit(slot, 0);
		}

		void Texture2D::init(MagFilter magFilter, MinFilter minFilter) {
			GLenum internaFormat = GL_RGB8, incomingFormat = GL_RGB;
			if (m_Image.getChannels() == 3) {
				internaFormat = GL_RGB8;
				incomingFormat = GL_RGB;
			}
			else if (m_Image.getChannels() == 4) {
				internaFormat = GL_RGBA8;
				incomingFormat = GL_RGBA;
			}
			
			glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
			glTextureStorage2D(m_TextureID, 1, internaFormat, m_Image.getWidth(), m_Image.getHeight());

			glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, static_cast<std::int32_t>(magFilter));
			glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, static_cast<std::int32_t>(minFilter));

			glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Image.getWidth(), m_Image.getHeight(), incomingFormat, GL_UNSIGNED_BYTE, m_Image.getBuffer());
		}
	}
}