#pragma once

#include "Texture2D.hpp"

#include <cstdint>
#include <memory>

namespace Hart {
	struct FrameBufferSpecification {
		uint32_t width;
		uint32_t height;
	};

	class FrameBuffer {
	public:
		FrameBuffer(const FrameBufferSpecification& frameBufferSpec);
		~FrameBuffer();

		void bind() const;

		inline const FrameBufferSpecification& getSpec() const { return m_FrameBufferSpec; }
		inline const std::shared_ptr<Texture2D>& getColorAttachment() const { return m_ColorBufferAttachment; }
		inline const std::shared_ptr<Texture2D>& getDepthStencilAttachment() const { return m_DepthStencilBufferAttachment; }

	private:
		uint32_t m_ID = 0;
		FrameBufferSpecification m_FrameBufferSpec;
		std::shared_ptr<Texture2D> m_ColorBufferAttachment;
		std::shared_ptr<Texture2D> m_DepthStencilBufferAttachment;
	};
}
