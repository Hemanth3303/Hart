#include "HartPch.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	namespace Graphics {
        void RenderCommand::Init() {
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        void RenderCommand::SetClearColor(const Maths::Vec4& color) {
			glClearColor(color.x / 255.0f, color.y / 255.0f, color.z / 255.0f, color.w / 255.0f);
		}

		void RenderCommand::Clear() {
			// TODO: ask for flags to what to clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void RenderCommand::SetViewPort(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height) {
			glViewport(x, y, width, height);
		}

		void RenderCommand::DrawArrays(std::uint32_t vertexCount) {
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		}

		void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			// TODO: Give options to specify OpenGL primitive type
			glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}