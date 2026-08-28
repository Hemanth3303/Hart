#pragma once

#include "Texture2D.hpp"

#include <cstdint>
#include <memory>

namespace Hart {
	struct FrameBufferSpecification {
		int32_t width = -1;
		int32_t height = -1;
	};

	class FrameBuffer {
	public:
		FrameBuffer(const FrameBufferSpecification& frameBufferSpec);
		~FrameBuffer();

		void bind() const;

		void resize(int32_t width, int32_t height);

		inline uint32_t getID() const { return m_ID; }
		inline const FrameBufferSpecification& getSpec() const { return m_FrameBufferSpec; }
		inline const std::shared_ptr<Texture2D>& getColorAttachment() const { return m_ColorBufferAttachment; }
		inline const std::shared_ptr<Texture2D>& getDepthStencilAttachment() const { return m_DepthStencilBufferAttachment; }

		static std::shared_ptr<FrameBuffer> GetDefaultFrameBuffer();

	private:
		FrameBuffer() = default;

		void init();
		void createAttachments();
		void deinit();

	private:
		uint32_t m_ID = 0;
		FrameBufferSpecification m_FrameBufferSpec;
		std::shared_ptr<Texture2D> m_ColorBufferAttachment = nullptr;
		std::shared_ptr<Texture2D> m_DepthStencilBufferAttachment = nullptr;
	};
}
