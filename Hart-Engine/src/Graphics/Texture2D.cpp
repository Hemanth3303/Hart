#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "glad/glad.h"

namespace Hart {
	Texture2D::Texture2D(const Image& image, const Texture2DSpecification& texture2DSpecs)
		: m_Image(image), m_TextureSpec(texture2DSpecs) {

		init();
	}

	Texture2D::Texture2D(const std::string& filePath, const Texture2DSpecification& texture2DSpecs)
		: m_Image(filePath), m_TextureSpec(texture2DSpecs) {

		init();
	}

	Texture2D::Texture2D(std::uint32_t* buffer, std::uint32_t width, std::uint32_t height, std::uint32_t channels, const Texture2DSpecification& texture2DSpecs)
		: m_Image(buffer, width, height, channels), m_TextureSpec(texture2DSpecs) {

		init();
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture2D::bind(std::uint32_t slot) const {
		m_Slot = slot;
		glBindTextureUnit(m_Slot, m_TextureID);
	}

	void Texture2D::unbind() const {
		glBindTextureUnit(m_Slot, 0);
	}

    void Texture2D::setBuffer(std::uint32_t* buffer) {
		m_Image.setBuffer(buffer);
		uploadBuffer();
    }

	bool Texture2D::operator==(const Texture2D& other) const {
		return (m_TextureID == other.m_TextureID);
	}

	void Texture2D::init() {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		m_InternalFormat = GL_RGB8;
		m_IncomingFormat = GL_RGB;

		if (m_Image.getChannels() == 3) {
			m_InternalFormat = GL_RGB8;
			m_IncomingFormat = GL_RGB;
		}
		else if (m_Image.getChannels() == 4) {
			m_InternalFormat = GL_RGBA8;
			m_IncomingFormat = GL_RGBA;
		}

		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_Image.getWidth(), m_Image.getHeight());

		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, static_cast<std::int32_t>(m_TextureSpec.magFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, static_cast<std::int32_t>(m_TextureSpec.minFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, static_cast<std::int32_t>(m_TextureSpec.repeatX));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, static_cast<std::int32_t>(m_TextureSpec.repeatY));

		uploadBuffer();

		if (m_TextureSpec.generateMipMaps == true) {
			glGenerateTextureMipmap(m_TextureID);
		}
	}

	void Texture2D::uploadBuffer() {
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Image.getWidth(), m_Image.getHeight(), m_IncomingFormat, GL_UNSIGNED_BYTE, m_Image.getBuffer());
	}

	bool operator==(const std::shared_ptr<Texture2D>& left, const std::shared_ptr<Texture2D>& right) {
		return ((*left.get()) == (*right.get()));
	}
}