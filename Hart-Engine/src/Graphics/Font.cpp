#include "HartPch.hpp"
#include "Font.hpp"
#include "Core/Assert.hpp"
#include "Utils/FileManager.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	Font::Font(const std::string& filePath, const float fontSize)
		: m_FontSize(fontSize) {
		if (!FileManager::FileExists(filePath)) {
			HART_ENGINE_ERROR("Font " + filePath + " not found");
			return;
		}
		m_FileSize = FileManager::GetFileSizeInBytes(filePath);
		m_FontDataBuffer = FileManager::ReadBinaryFromFile(filePath);

		int32_t fontCount = stbtt_GetNumberOfFonts(reinterpret_cast<const unsigned char*>(m_FontDataBuffer.data()));
		HART_DEBUG_ASSERT((fontCount == 1), "The font file contains more than one font. This is currently not supported");

		m_FontTextureSpecification.width = 1024;
		m_FontTextureSpecification.height = 1024;
		m_FontTextureSpecification.numberOfChannels = 1;
		m_FontTextureSpecification.magFilter = TextureMagFilter::Linear;
		m_FontTextureSpecification.minFilter = TextureMinFilter::LinearLinear;

		m_FontAtlasBitmap.reserve(m_FontTextureSpecification.width * m_FontTextureSpecification.height);

		stbtt_PackBegin(
			&m_PackContext,
			reinterpret_cast<unsigned char*>(m_FontAtlasBitmap.data()),
			m_FontTextureSpecification.width,
			m_FontTextureSpecification.height,
			0,
			1,
			nullptr);

		stbtt_PackFontRange(
			&m_PackContext,
			reinterpret_cast<uint8_t*>(m_FontDataBuffer.data()),
			0,
			m_FontSize,
			m_CodePointFirstChar,
			m_NumberOfCharsToInclude,
			m_PackedChars.data());

		stbtt_PackEnd(&m_PackContext);

		for (int i = 0; i < m_NumberOfCharsToInclude; i++) {
			float unusedX, unusedY;

			stbtt_GetPackedQuad(
				m_PackedChars.data(),
				m_FontTextureSpecification.width,
				m_FontTextureSpecification.height,
				i,
				&unusedX,
				&unusedY,
				&m_AlignedQuads[i],
				0);
		}
	}

	Font::~Font() {
	}
}
