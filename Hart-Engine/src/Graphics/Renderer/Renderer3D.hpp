#pragma once

#include "HartPch.hpp"
#include "RenderCommand.hpp"
#include "../Camera/PerspectiveCamera.hpp"
#include "../Primitives/VertexArray.hpp"
#include "../Primitives/Shader.hpp"
#include "../Primitives/Texture2D.hpp"

namespace Hart {
	namespace Graphics {
		struct SceneData {
			Maths::Mat4 viewProjectionMatrix;
		};
		class Renderer3D {
		public:
			static void Init();
			static void DeInit();
			
			static void BeginScene(PerspectiveCamera& camera);
			static void EndScene();

			static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Maths::Mat4& transformationMatrix = Maths::Mat4(1.0f));
		private:
			static std::unique_ptr<SceneData> s_SceneData;
		};
	}
}