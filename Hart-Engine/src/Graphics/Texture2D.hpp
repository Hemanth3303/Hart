/*
* OpenGL Textures
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
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

	struct Texture2DSpecification {
	public:
		std::uint32_t width = 0, height = 0, numberOfChannels = 4;
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
		Texture2D(const std::string& filePath, const Texture2DSpecification& texture2DSpecs = {});
		Texture2D(std::uint32_t* buffer, const Texture2DSpecification& texture2DSpecs = {});
		~Texture2D();

		void bind(std::uint32_t slot = 0) const;
		void unbind() const;
		
		void setBuffer(std::uint32_t* buffer);
		void setBuffer(std::uint32_t* buffer, const Texture2DSpecification& texture2DSpecs);

		inline const std::uint32_t getId() const { return m_TextureID; }
		inline const std::uint32_t* getBuffer() const { return m_Buffer; }
		inline const std::int32_t getSlot() const { return m_Slot; }
		inline const Texture2DSpecification& getSpecs() const { return m_TextureSpec; }
		inline const std::uint32_t getWidth() const { return m_TextureSpec.width; }
		inline const std::uint32_t getHeight() const { return m_TextureSpec.height; }

		bool operator==(const Texture2D& other) const;
		friend bool operator==(const std::shared_ptr<Texture2D>& left, const std::shared_ptr<Texture2D>& right);
	private:
		void init();
		void deinit();
	private:
		std::uint32_t m_TextureID = 0;
		std::uint32_t* m_Buffer;
		mutable std::uint32_t m_Slot = 0;
		bool m_loadedFromStbi = false;
		Texture2DSpecification m_TextureSpec;
		std::uint32_t m_InternalFormat = 0;
		std::uint32_t m_IncomingFormat = 0;
	};
	bool operator==(const std::shared_ptr<Texture2D>& left, const std::shared_ptr<Texture2D>& right);
}