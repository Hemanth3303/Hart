#pragma once

#include "OpenGL/Texture2D.hpp"

#include "stb_truetype.h"

#include <vector>
#include <array>
#include <cstddef>
#include <memory>

namespace Hart {
	class Font {
	public:
		Font(const std::string& filePath, const float fontSize = 64.0f);
		~Font();

		inline float getFontSize() const { return m_FontSize; }
		inline const std::vector<std::byte>& getFontBuffer() const { return m_FontDataBuffer; }
		inline stbtt_packedchar* getSTBTTPackedChar() { return m_PackedChars.data(); }
		inline uint32_t getCodePointFirstChar() const { return m_CodePointFirstChar; }
		inline uint32_t getNumberOfCharsToInclude() const { return m_NumberOfCharsToInclude; }
		inline const std::shared_ptr<Texture2D>& getTexture() const { return m_FontTexture; }

		static bool Equals(const Font& lhs, const Font& rhs);
		static bool Equals(const std::shared_ptr<Font>& lhs, const std::shared_ptr<Font>& rhs);

	private:
		std::vector<std::byte> m_FontDataBuffer;
		std::vector<std::byte> m_FontAtlasBitmap;

		const float m_FontSize;
		static constexpr uint32_t m_CodePointFirstChar = 32; // ASCII Space
		static constexpr uint32_t m_NumberOfCharsToInclude = 95; // ASCII(32)[Space] to ASCII(126)[~]

		std::array<stbtt_packedchar, m_NumberOfCharsToInclude> m_PackedChars;
		stbtt_pack_context m_PackContext;

		Texture2DSpecification m_FontTextureSpecification;
		std::shared_ptr<Texture2D> m_FontTexture = nullptr;
	};
}
