#pragma once

#include "HartPch.hpp"
#include "Texture2D.hpp"

#include "stb_truetype.h"

namespace Hart {
	class Font {
	public:
		Font(const std::string& filePath, const float fontSize = 64.0f);
		~Font();

		inline const float getFontSize() { return m_FontSize; }
		inline void* getFontBufferData() { return m_FontDataBuffer.data(); }
		inline std::uint32_t* getFontAtlasBitmapData() { return m_FontAtlasBitmap.data(); }
		inline const Texture2DSpecification& getTextureSpecification() { return m_FontTextureSpecification; }
		inline stbtt_packedchar* getSTBTTPackedChar() { return m_PackedChars.data(); }
		inline stbtt_aligned_quad* getSTBTTAlignedQuads() { return m_AlignedQuads.data(); }
		inline const std::uint32_t getCodePointFirstChar() { return m_CodePointFirstChar; }
		inline const std::uint32_t getNumberOfCharsToInclude() { return m_NumberOfCharsToInclude; }
	private:
		std::size_t m_FileSize = 0;
		std::vector<void*> m_FontDataBuffer;
		std::vector<std::uint32_t> m_FontAtlasBitmap;
		Texture2DSpecification m_FontTextureSpecification;

		const float m_FontSize;
		static constexpr std::uint32_t m_CodePointFirstChar = 32; // ASCII Space
		static constexpr std::uint32_t m_NumberOfCharsToInclude = 95; // ASCII(32)[Space] to ASCII(126)[~]

		std::array<stbtt_packedchar, m_NumberOfCharsToInclude> m_PackedChars;
		std::array<stbtt_aligned_quad, m_NumberOfCharsToInclude> m_AlignedQuads;
		stbtt_pack_context m_PackContext;
	};
}
