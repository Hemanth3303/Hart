#pragma once

#include "HartPch.hpp"
#include "RenderCommand.hpp"
#include "OrthographicCamera.hpp"
#include "../Primitives/VertexArray.hpp"
#include "../Primitives/Shader.hpp"

namespace Hart {
	namespace Graphics {
		struct SceneData {
			Maths::Mat4 viewProjectionMatrix;
		};
		class Renderer {
		public:
			static void BeginScene(OrthographicCamera& camera); //TODO: Add scene parameters
			static void EndScene();

			static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Maths::Mat4& transformationMatrix = Maths::Mat4(1.0f));
		private:
			static std::unique_ptr<SceneData> s_SceneData;
		};
	}
}