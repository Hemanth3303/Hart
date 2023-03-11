#include "HartPch.hpp"
#include "Texture2D.hpp"
#include "Core/HartApplication.hpp"

namespace Hart {
	namespace Graphics {
		// start from -1 because the first texture created set no of textures to -1+1==0
		int32_t Texture2D::s_NoOfTextures = -1;

        Texture2D::Texture2D(const std::string& fileName, GLint magFilterParam, GLint minFliterParam)
			: m_Image(fileName) {

			init(magFilterParam, minFliterParam);
        }

        Texture2D::Texture2D(uint32_t* buffer, int32_t width, int32_t height, int32_t noOfChannels, GLint magFilterParam, GLint minFliterParam)
			: m_Image(buffer, width, height, noOfChannels) {

			init(magFilterParam, minFliterParam);
        }

        Texture2D::~Texture2D() {
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
		void Texture2D::init(GLint magFilterParam, GLint minFliterParam) {
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
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFliterParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterParam);

			HART_ENGINE_LOG(std::string("Creating Texture Number: ") + std::to_string(m_TextureSlot));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Image.getWidth(), m_Image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Image.getImageData());
			glGenerateMipmap(GL_TEXTURE_2D);

			unbind();
		}
    }
}