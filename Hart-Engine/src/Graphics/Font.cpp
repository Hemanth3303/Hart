#include "HartPch.hpp"
#include "Font.hpp"
#include "Core/Assert.hpp"
#include "Utils/FileManager.hpp"
#include "Utils/Logger.hpp"

namespace Hart {
	Font::Font(const std::string& filePath, const float fontSize)
		: m_FontSize(fontSize) {
		bool fileExists = FileManager::FileExists(filePath);
		HART_DEBUG_ASSERT(fileExists, "Reason: The font file \"", filePath, "\" not found. ", "Is the name and/or path correct?");
		if (!fileExists) {
			HART_ENGINE_ERROR(LogSource::EngineGraphics, "The font file \"", filePath, "\" not found. ", "Is the name and/or path correct?");
			return;
		}

		m_FontDataBuffer = FileManager::ReadBinaryFromFile(filePath);

		int32_t fontCount = stbtt_GetNumberOfFonts(reinterpret_cast<const unsigned char*>(m_FontDataBuffer.data()));
		HART_DEBUG_ASSERT((fontCount == 1), "The font file contains more than one font. This is currently not supported");

		m_FontTextureSpecification.width = 1024;
		m_FontTextureSpecification.height = 1024;
		m_FontTextureSpecification.numberOfChannels = 1;
		m_FontTextureSpecification.internalFormat = TextureInternalFormat::R8;
		m_FontTextureSpecification.incomingFormat = TextureIncomingFormat::Red;
		m_FontTextureSpecification.magFilter = TextureMagFilter::Linear;
		m_FontTextureSpecification.minFilter = TextureMinFilter::LinearLinear;
		m_FontTextureSpecification.generateMipMaps = true;

		m_FontAtlasBitmap.resize(m_FontTextureSpecification.width * m_FontTextureSpecification.height);

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
			reinterpret_cast<unsigned char*>(m_FontDataBuffer.data()),
			0,
			m_FontSize,
			m_CodePointFirstChar,
			m_NumberOfCharsToInclude,
			m_PackedChars.data());

		stbtt_PackEnd(&m_PackContext);
	}

	Font::~Font() {
	}
}
