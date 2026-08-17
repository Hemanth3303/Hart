#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "glad/glad.h"
#include "stb_image.h"
#include "Utils/FileManager.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	Texture2D::Texture2D(const std::string& filePath, const Texture2DSpecification& texture2DSpecs)
		: m_loadedFromStbi(true), m_TextureSpec(texture2DSpecs) {

		if (!FileManager::FileExists(filePath)) {
			HART_ENGINE_ERROR("File " + filePath + " does not exists", "Is the name and/or path correct?");
			m_loadedFromStbi = false;
			return;
		}

		int32_t width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		m_Buffer = reinterpret_cast<std::byte*>(stbi_load(filePath.c_str(), &width, &height, &channels, 0));
		stbi_set_flip_vertically_on_load(false);

		m_TextureSpec.width = width;
		m_TextureSpec.height = height;
		m_TextureSpec.numberOfChannels = channels;

		init();
	}

	Texture2D::Texture2D(std::byte* buffer, const Texture2DSpecification& texture2DSpecs)
		: m_Buffer(buffer), m_loadedFromStbi(false), m_TextureSpec(texture2DSpecs) {

		init();
	}

	Texture2D::~Texture2D() {
		deinit();
	}

	void Texture2D::bind(uint32_t slot) const {
		m_Slot = slot;
		glBindTextureUnit(m_Slot, m_TextureID);
	}

	void Texture2D::unbind() const {
		glBindTextureUnit(m_Slot, 0);
	}

	void Texture2D::setBuffer(std::byte* buffer) {
		deinit();
		m_loadedFromStbi = false;
		m_Buffer = buffer;
		init();
	}

	void Texture2D::setBuffer(std::byte* buffer, const Texture2DSpecification& texture2DSpecs) {
		deinit();
		m_loadedFromStbi = false;
		m_TextureSpec = texture2DSpecs;
		m_Buffer = buffer;
		init();
	}

	bool Texture2D::operator==(const Texture2D& other) const {
		return (m_TextureID == other.m_TextureID);
	}

	void Texture2D::init() {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		HART_DEBUG_ASSERT((m_TextureSpec.numberOfChannels > 0) && (m_TextureSpec.numberOfChannels < 5),
						  "Invalid number of channels in texture");

		m_InternalFormat = GL_RGB8;
		m_IncomingFormat = GL_RGB;

		if (m_TextureSpec.numberOfChannels == 1) {
			m_InternalFormat = GL_R8;
			m_IncomingFormat = GL_RED;
		}
		else if (m_TextureSpec.numberOfChannels == 2) {
			m_InternalFormat = GL_RG8;
			m_IncomingFormat = GL_RG;
		}
		else if (m_TextureSpec.numberOfChannels == 3) {
			m_InternalFormat = GL_RGB8;
			m_IncomingFormat = GL_RGB;
		}
		else if (m_TextureSpec.numberOfChannels == 4) {
			m_InternalFormat = GL_RGBA8;
			m_IncomingFormat = GL_RGBA;
		}
		else {
			return;
		}

		glTextureStorage2D(m_TextureID, 1, m_InternalFormat, m_TextureSpec.width, m_TextureSpec.height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, static_cast<int32_t>(m_TextureSpec.magFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, static_cast<int32_t>(m_TextureSpec.minFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, static_cast<int32_t>(m_TextureSpec.repeatX));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, static_cast<int32_t>(m_TextureSpec.repeatY));

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_TextureSpec.width, m_TextureSpec.height, m_IncomingFormat, GL_UNSIGNED_BYTE, m_Buffer);

		if (m_TextureSpec.generateMipMaps == true) {
			glGenerateTextureMipmap(m_TextureID);
		}
	}

	void Texture2D::deinit() {
		if (m_loadedFromStbi == true) {
			stbi_image_free(m_Buffer);
		}

		glDeleteTextures(1, &m_TextureID);
	}

	bool operator==(const std::shared_ptr<Texture2D>& left, const std::shared_ptr<Texture2D>& right) {
		return ((*left.get()) == (*right.get()));
	}
}
