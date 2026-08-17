#pragma once

#include "Texture2D.hpp"

#include "stb_truetype.h"

#include <vector>
#include <array>
#include <cstddef>

namespace Hart {
	class Font {
	public:
		Font(const std::string& filePath, const float fontSize = 64.0f);
		~Font();

		inline float getFontSize() const { return m_FontSize; }
		inline const std::vector<std::byte>& getFontBuffer() const { return m_FontDataBuffer; }
		inline std::vector<std::byte>& getFontAtlasBitmap() { return m_FontAtlasBitmap; }
		inline const Texture2DSpecification& getTextureSpecification() const { return m_FontTextureSpecification; }
		inline stbtt_packedchar* getSTBTTPackedChar() { return m_PackedChars.data(); }
		inline stbtt_aligned_quad* getSTBTTAlignedQuads() { return m_AlignedQuads.data(); }
		inline const uint32_t getCodePointFirstChar() { return m_CodePointFirstChar; }
		inline const uint32_t getNumberOfCharsToInclude() { return m_NumberOfCharsToInclude; }

	private:
		std::vector<std::byte> m_FontDataBuffer;
		std::vector<std::byte> m_FontAtlasBitmap;
		Texture2DSpecification m_FontTextureSpecification;

		const float m_FontSize;
		static constexpr uint32_t m_CodePointFirstChar = 32; // ASCII Space
		static constexpr uint32_t m_NumberOfCharsToInclude = 95; // ASCII(32)[Space] to ASCII(126)[~]

		std::array<stbtt_packedchar, m_NumberOfCharsToInclude> m_PackedChars;
		std::array<stbtt_aligned_quad, m_NumberOfCharsToInclude> m_AlignedQuads;
		stbtt_pack_context m_PackContext;
	};
}
