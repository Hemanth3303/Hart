/*
 * OpenGL Textures
 */

#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <cstddef>

#include "glad/glad.h"

namespace Hart {
	enum class TextureMagFilter {
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR,
	};

	enum class TextureMinFilter {
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR,

		NearestNearest = GL_NEAREST_MIPMAP_NEAREST,
		LinearNearest = GL_LINEAR_MIPMAP_NEAREST,
		NearestLinear = GL_NEAREST_MIPMAP_LINEAR,
		LinearLinear = GL_LINEAR_MIPMAP_LINEAR,
	};

	enum class TextureRepeatFilter {
		Repeat = GL_REPEAT,
		MirroredRepeat = GL_MIRRORED_REPEAT,
		ClampToEdge = GL_CLAMP_TO_EDGE,
		ClampToBorder = GL_CLAMP_TO_BORDER,
	};

	enum class TextureInternalFormat {
		R8 = GL_R8,
		RG8 = GL_RG8,
		RGB8 = GL_RGB8,
		RGBA8 = GL_RGBA8,

		Depth24Stencil8 = GL_DEPTH24_STENCIL8,
	};

	enum class TextureIncomingFormat {
		Red = GL_RED,
		RG = GL_RG,
		RGB = GL_RGB,
		RGBA = GL_RGBA,

		DepthStencil = GL_DEPTH_STENCIL,
	};

	/**
	 * If generateMipMaps is set to false, only use TextureMinFilter::Linear or TextureMinFilter::Nearest.
	 * Don't set numberOfChannels manually for textures loaded from disk using stbi
	 */
	struct Texture2DSpecification {
		uint32_t width = 0;
		uint32_t height = 0;
		uint32_t numberOfChannels = 0;

		TextureInternalFormat internalFormat = TextureInternalFormat::RGBA8;
		TextureIncomingFormat incomingFormat = TextureIncomingFormat::RGBA;

		TextureMagFilter magFilter = TextureMagFilter::Linear;
		TextureMinFilter minFilter = TextureMinFilter::LinearLinear;

		TextureRepeatFilter repeatX = TextureRepeatFilter::Repeat;
		TextureRepeatFilter repeatY = TextureRepeatFilter::Repeat;

		bool generateMipMaps = true;
	};

	// OpenGL Textures
	class Texture2D {
	public:
		// width, height and number of channels of specification will be overwritten by the actual values from image file
		Texture2D(const std::string& filePath, const Texture2DSpecification& textureSpec = {});
		Texture2D(std::byte* buffer, const Texture2DSpecification& textureSpec = {});
		Texture2D(const Texture2DSpecification& textureSpec);
		~Texture2D();

		void bind(uint32_t slot = 0) const;
		void unbind() const;

		void uploadNewBuffer(std::byte* buffer);
		void uploadNewBuffer(std::byte* buffer, const Texture2DSpecification& textureSpec);

		inline uint32_t getID() const { return m_TextureID; }
		// For some reason, opengl wants to bind the texture slot with glBindTextureUnit as unsigned int,
		// but to set the uniform as a signed int, idk why
		inline int32_t getSlot() const { return m_Slot; }
		inline const Texture2DSpecification& getSpec() const { return m_TextureSpec; }
		inline uint32_t getWidth() const { return m_TextureSpec.width; }
		inline uint32_t getHeight() const { return m_TextureSpec.height; }

		static bool Equals(const Texture2D& lhs, const Texture2D& rhs);
		static bool Equals(const std::shared_ptr<Texture2D>& lhs, const std::shared_ptr<Texture2D>& rhs);

	private:
		void init();
		void deinit();

	private:
		uint32_t m_TextureID = 0;
		std::byte* m_Buffer = nullptr;
		mutable uint32_t m_Slot = 0;
		Texture2DSpecification m_TextureSpec;
	};
}
