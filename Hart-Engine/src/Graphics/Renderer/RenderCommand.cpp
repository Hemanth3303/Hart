#include "HartPch.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	namespace Graphics {
        void RenderCommand::Init() {
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			HART_ENGINE_LOG("Initializing OpenGL Renderer");
			HART_ENGINE_LOG(
				"OpenGL Renderer Info:",
				std::string("\t\t\t\t\tVendor: ") + reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
				std::string("\t\t\t\t\tRenderer: ") + reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
				std::string("\t\t\t\t\tVersion: ") + reinterpret_cast<const char*>(glGetString(GL_VERSION))
			);
        }
        void RenderCommand::DeInit() {
			HART_ENGINE_LOG("DeInitializing OpenGL Renderer");
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

		std::int64_t RenderCommand::getMaxTextureSlotsPerShader() {
			std::int64_t maxNoOfTextureSlotsPerShader;
			glGetInteger64v(GL_MAX_TEXTURE_IMAGE_UNITS, &maxNoOfTextureSlotsPerShader);

			return maxNoOfTextureSlotsPerShader;
		}

		const std::int64_t RenderCommand::getMaxTextureSlotsTotal() {
			return GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
		}

		void RenderCommand::DrawArrays(std::uint32_t vertexCount) {
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
		}

		void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, std::uint32_t indexCount) {
			/*if (indexCount > 0) {
				std::uint32_t count = vertexArray->getIndexBuffer()->getIndexCount();
			}
			else {
				std::uint32_t count = indexCount;
			}*/
			std::uint32_t count = (indexCount == 0 ? vertexArray->getIndexBuffer()->getIndexCount() : indexCount);

			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		}
	}
}