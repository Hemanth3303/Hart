#include "HartPch.hpp"
#include "FrameBuffer.hpp"
#include "Core/Application.hpp"

namespace Hart {
	FrameBuffer::FrameBuffer(const FrameBufferSpecification& frameBufferSpec)
		: m_FrameBufferSpec(frameBufferSpec) {
		glCreateFramebuffers(1, &m_ID);

		Texture2DSpecification fboColorAttachmentSpec = {
			.width = static_cast<uint32_t>(m_FrameBufferSpec.width),
			.height = static_cast<uint32_t>(m_FrameBufferSpec.height),

			.internalFormat = TextureInternalFormat::RGBA8,
			.incomingFormat = TextureIncomingFormat::RGBA,

			.magFilter = TextureMagFilter::Linear,
			.minFilter = TextureMinFilter::Linear,

			.repeatX = TextureRepeatFilter::ClampToEdge,
			.repeatY = TextureRepeatFilter::ClampToEdge,

			.generateMipMaps = false,
		};
		m_ColorBufferAttachment = std::make_shared<Texture2D>(fboColorAttachmentSpec);

		Texture2DSpecification fboDepthStencilAttachmentSpec = {
			.width = static_cast<uint32_t>(m_FrameBufferSpec.width),
			.height = static_cast<uint32_t>(m_FrameBufferSpec.height),

			.internalFormat = TextureInternalFormat::Depth24Stencil8,
			.incomingFormat = TextureIncomingFormat::DepthStencil,

			.magFilter = TextureMagFilter::Nearest,
			.minFilter = TextureMinFilter::Nearest,

			.repeatX = TextureRepeatFilter::ClampToEdge,
			.repeatY = TextureRepeatFilter::ClampToEdge,

			.generateMipMaps = false,
		};
		m_DepthStencilBufferAttachment = std::make_shared<Texture2D>(fboDepthStencilAttachmentSpec);

		glNamedFramebufferTexture(m_ID, GL_COLOR_ATTACHMENT0, m_ColorBufferAttachment->getID(), 0);
		glNamedFramebufferTexture(m_ID, GL_DEPTH_STENCIL_ATTACHMENT, m_DepthStencilBufferAttachment->getID(), 0);
		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
		glNamedFramebufferDrawBuffers(m_ID, 1, drawBuffers);

		GLenum status = glCheckNamedFramebufferStatus(m_ID, GL_FRAMEBUFFER);
		HART_DEBUG_ASSERT(
			status == GL_FRAMEBUFFER_COMPLETE,
			"Reason: Incomplete framebuffer");
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			HART_ENGINE_ERROR("incomplete framebuffer");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer() {
		glDeleteFramebuffers(1, &m_ID);
	}

	void FrameBuffer::bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	}

	FrameBuffer FrameBuffer::GetDefaultFrameBuffer() {
		FrameBuffer fbo;
		fbo.m_ID = 0;

		return fbo;
	}
}
