#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "glad/glad.h"
#include "stb_image.h"

namespace Hart {
	Texture2D::Texture2D(const std::string& filePath, const Texture2DSpecification& texture2DSpecs)
		: m_loadedFromStbi(true), m_TextureSpec(texture2DSpecs) {
		
		if (!FileManager::FileExists(filePath)) {
			HART_ENGINE_ERROR("File " + filePath + " does not exits", "Is the name and/or path correct?");
		}
		else {
			int32_t width, height, channels;

			stbi_set_flip_vertically_on_load(true);
			m_Buffer = reinterpret_cast<std::uint32_t*>(stbi_load(filePath.c_str(), &width, &height, &channels, 0));
			stbi_set_flip_vertically_on_load(false);

			m_TextureSpec.width = width;
			m_TextureSpec.height = height;
			m_TextureSpec.numberOfChannels = channels;
		}

		init();
	}

	Texture2D::Texture2D(std::uint32_t* buffer, const Texture2DSpecification& texture2DSpecs)
		: m_Buffer(buffer), m_loadedFromStbi(false), m_TextureSpec(texture2DSpecs) {

		init();
	}

	Texture2D::~Texture2D() {
		deinit();
	}

	void Texture2D::bind(std::uint32_t slot) const {
		m_Slot = slot;
		glBindTextureUnit(m_Slot, m_TextureID);
	}

	void Texture2D::unbind() const {
		glBindTextureUnit(m_Slot, 0);
	}

    void Texture2D::setBuffer(std::uint32_t* buffer) {
		deinit();
		m_Buffer = buffer;
		init();
    }

	void Texture2D::setBuffer(std::uint32_t* buffer, const Texture2DSpecification& texture2DSpecs) {
		deinit();
		m_TextureSpec = texture2DSpecs;
		m_Buffer = buffer;
		init();
	}

	bool Texture2D::operator==(const Texture2D& other) const {
		return (m_TextureID == other.m_TextureID);
	}

	void Texture2D::init() {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		m_InternalFormat = GL_RGB8;
		m_IncomingFormat = GL_RGB;

		if (m_TextureSpec.numberOfChannels == 3) {
			m_InternalFormat = GL_RGB8;
			m_IncomingFormat = GL_RGB;
		}
		else if (m_TextureSpec.numberOfChannels == 4) {
			m_InternalFormat = GL_RGBA8;
			m_IncomingFormat = GL_RGBA;
		}
		else if (m_TextureSpec.numberOfChannels == 1) {
			m_InternalFormat = GL_R8;
			m_IncomingFormat = GL_RED;
		}

		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_TextureSpec.width, m_TextureSpec.height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, static_cast<std::int32_t>(m_TextureSpec.magFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, static_cast<std::int32_t>(m_TextureSpec.minFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, static_cast<std::int32_t>(m_TextureSpec.repeatX));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, static_cast<std::int32_t>(m_TextureSpec.repeatY));

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_TextureSpec.width, m_TextureSpec.height, m_IncomingFormat, GL_UNSIGNED_BYTE, m_Buffer);

		if (m_TextureSpec.generateMipMaps == true) {
			glGenerateTextureMipmap(m_TextureID);
		}
	}

	void Texture2D::deinit() {
		if (m_loadedFromStbi == true) {
			stbi_image_free(reinterpret_cast<void*>(m_Buffer));
		}

		glDeleteTextures(1, &m_TextureID);
	}

	bool operator==(const std::shared_ptr<Texture2D>& left, const std::shared_ptr<Texture2D>& right) {
		return ((*left.get()) == (*right.get()));
	}
}