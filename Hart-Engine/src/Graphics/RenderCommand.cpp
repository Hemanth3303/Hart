#include "HartPch.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	namespace Graphics {
		void RenderCommand::SetClearColor(const Maths::Vec4& color) {
			glClearColor(color.x, color.y, color.z, color.w);
		}

		void RenderCommand::Clear() {
			// TODO: ask for flags to what to clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			// TODO: Give options to specify OpenGL primitive type
			glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
}