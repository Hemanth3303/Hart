#pragma once

#include "HartPch.hpp"
#include "Texture2D.hpp"

#include "stb_truetype.h"

namespace Hart {
	class Font {
	public:
		Font(const std::string& filePath);
		~Font();

		inline const std::size_t getFileSizeInBytes() { return m_FileSize; }
		inline void* getFontBufferData() { return m_FontDataBuffer.data(); }
		inline std::uint32_t* getFontAtlasBitmap() { return m_FontAtlasBitmap.data(); }
		inline const Texture2DSpecification& getTextureSpecification() { return m_FontTextureSpecification; }
	private:
		std::size_t m_FileSize = 0;
		std::vector<void*> m_FontDataBuffer;
		std::vector<std::uint32_t> m_FontAtlasBitmap;
		Texture2DSpecification m_FontTextureSpecification;

		float m_FontSize = 64.0f;
		static constexpr std::uint32_t m_CodePointFirstChar = 32; // ASCII Space
		static constexpr std::uint32_t m_NumberOfCharsToInclude = 95; // ASCII(32)[Space] to ASCII(126)[~]

		std::array<stbtt_packedchar, m_NumberOfCharsToInclude> m_PackedChars;
		std::array<stbtt_aligned_quad, m_NumberOfCharsToInclude> m_AlignedQuads;
		stbtt_pack_context m_PackContext;
	};
}