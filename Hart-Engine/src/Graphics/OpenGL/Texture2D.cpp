#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "Core/Assert.hpp"
#include "Utils/Logger.hpp"
#include "Utils/FileManager.hpp"
#include "Maths/MathFunctions.hpp"

#include "stb_image.h"

namespace Hart {
	uint32_t calculateMipMapLevels(uint32_t width, uint32_t height);

	Texture2D::Texture2D(const std::string& filePath, const Texture2DSpecification& textureSpec)
		: m_TextureSpec(textureSpec) {
		if (!FileManager::FileExists(filePath)) {
			HART_ENGINE_ERROR("File ", filePath, " does not exist. ", "Is the name and/or path correct?");
			return;
		}

		int32_t width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		m_Buffer = reinterpret_cast<std::byte*>(stbi_load(filePath.c_str(), &width, &height, &channels, 0));
		stbi_set_flip_vertically_on_load(false);

		if (m_Buffer == nullptr) {
			HART_ENGINE_ERROR("Failed to load texture ", filePath);
			return;
		}

		m_TextureSpec.width = width;
		m_TextureSpec.height = height;
		m_TextureSpec.numberOfChannels = channels;

		switch (m_TextureSpec.numberOfChannels) {
			case 1:
				m_TextureSpec.internalFormat = TextureInternalFormat::R8;
				m_TextureSpec.incomingFormat = TextureIncomingFormat::Red;
				break;

			case 2:
				m_TextureSpec.internalFormat = TextureInternalFormat::RG8;
				m_TextureSpec.incomingFormat = TextureIncomingFormat::RG;
				break;

			case 3:
				m_TextureSpec.internalFormat = TextureInternalFormat::RGB8;
				m_TextureSpec.incomingFormat = TextureIncomingFormat::RGB;
				break;

			case 4:
				m_TextureSpec.internalFormat = TextureInternalFormat::RGBA8;
				m_TextureSpec.incomingFormat = TextureIncomingFormat::RGBA;
				break;

			default:
				HART_ENGINE_ERROR("Texture ", filePath, " has an invalid number of channels: ", channels);
				stbi_image_free(m_Buffer);
				m_Buffer = nullptr;
				return;
		}

		init();
		stbi_image_free(m_Buffer);
		m_Buffer = nullptr;
	}

	Texture2D::Texture2D(std::byte* buffer, const Texture2DSpecification& textureSpec)
		: m_Buffer(buffer), m_TextureSpec(textureSpec) {
		init();
	}

	Texture2D::Texture2D(const Texture2DSpecification& textureSpec)
		: m_TextureSpec(textureSpec) {
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

	void Texture2D::uploadNewBuffer(std::byte* buffer) {
		deinit();
		m_Buffer = buffer;
		init();
	}

	void Texture2D::uploadNewBuffer(std::byte* buffer, const Texture2DSpecification& textureSpec) {
		deinit();
		m_Buffer = buffer;
		m_TextureSpec = textureSpec;
		init();
	}

	bool Texture2D::Equals(const Texture2D& lhs, const Texture2D& rhs) {
		return (lhs.getID() == rhs.getID());
	}

	bool Texture2D::Equals(const std::shared_ptr<Texture2D>& lhs, const std::shared_ptr<Texture2D>& rhs) {
		return Texture2D::Equals(*lhs.get(), *rhs.get());
	}

	void Texture2D::init() {
		HART_DEBUG_ASSERT(
			m_TextureSpec.width > 0 && m_TextureSpec.height > 0,
			"Reason: Texture width and height must be greater than zero");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		uint32_t mipMapLevels = 1;
		if (m_TextureSpec.generateMipMaps) {
			mipMapLevels = calculateMipMapLevels(m_TextureSpec.width, m_TextureSpec.height);
		}

		glTextureStorage2D(m_TextureID, mipMapLevels, static_cast<GLenum>(m_TextureSpec.internalFormat), m_TextureSpec.width, m_TextureSpec.height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(m_TextureSpec.magFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(m_TextureSpec.minFilter));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, static_cast<GLint>(m_TextureSpec.repeatX));
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, static_cast<GLint>(m_TextureSpec.repeatY));

		if (m_Buffer == nullptr) {
			return;
		}

		GLenum incomingType = GL_UNSIGNED_BYTE;
		if (m_TextureSpec.incomingFormat == TextureIncomingFormat::DepthStencil) {
			incomingType = GL_UNSIGNED_INT_24_8;
		}

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_TextureSpec.width, m_TextureSpec.height, static_cast<GLenum>(m_TextureSpec.incomingFormat), incomingType, m_Buffer);

		if (m_TextureSpec.generateMipMaps) {
			glGenerateTextureMipmap(m_TextureID);
		}
	}

	void Texture2D::deinit() {
		glDeleteTextures(1, &m_TextureID);
		m_Buffer = nullptr;
	}

	uint32_t calculateMipMapLevels(uint32_t width, uint32_t height) {
		uint32_t mipMapLevels = static_cast<uint32_t>(Hart::floor(Hart::logBaseTwo(Hart::max(width, height))) + 1);
		return mipMapLevels;
	}
}
