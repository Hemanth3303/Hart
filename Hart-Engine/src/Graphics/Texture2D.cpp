#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "Core/HartApplication.hpp"

namespace Hart {
	namespace Graphics {
		// start from -1 because the first texture created set no of textures to -1+1==0
		int32_t Texture2D::s_NoOfTextures = -1;

        Texture2D::Texture2D(const std::string& fileName, MagFilterParams magFilterParam, MinFilterParams minFliterParam)
			: m_Image(fileName) {

			init(magFilterParam, minFliterParam);
        }

		Texture2D::Texture2D(const Image& image, MagFilterParams magFilterParam, MinFilterParams minFliterParam)
			:m_Image(image) {
			
			init(magFilterParam, minFliterParam);
		}

        Texture2D::Texture2D(uint32_t* dataBuffer, int32_t width, int32_t height, int32_t noOfChannels, MagFilterParams magFilterParam, MinFilterParams minFliterParam)
			: m_Image(dataBuffer, width, height, noOfChannels) {

			init(magFilterParam, minFliterParam);
        }

        Texture2D::~Texture2D() {
			HART_ENGINE_LOG(std::string("Deleting Texture Number: ") + std::to_string(m_TextureSlot));
			s_NoOfTextures -= 1;
			glDeleteTextures(1, &m_ID);
        }

        void Texture2D::bind() const {
			glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
			glBindTexture(GL_TEXTURE_2D, m_ID);
        }

        void Texture2D::unbind() const {
			glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
			glBindTexture(GL_TEXTURE_2D, 0);
        }
		void Texture2D::init(MagFilterParams magFilterParam, MinFilterParams minFliterParam) {
			if (s_NoOfTextures >= Application::s_Instance->getMaxTextureSlotsCombined()) {
				HART_ENGINE_ERROR("Can't have more textures");
				return;
			}

			s_NoOfTextures += 1;
			m_TextureSlot = s_NoOfTextures;
			if (m_Image.getImageData() == nullptr) {
				HART_ENGINE_ERROR("Failed To Create Texture");
				return;
			}

			glGenTextures(1, &m_ID);
			bind();

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int32_t>(minFliterParam));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int32_t>(magFilterParam));

			HART_ENGINE_LOG(std::string("Creating Texture Number: ") + std::to_string(m_TextureSlot));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Image.getWidth(), m_Image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image.getImageData());
			glGenerateMipmap(GL_TEXTURE_2D);

			unbind();
		}
    }
}