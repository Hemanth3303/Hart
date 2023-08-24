#pragma once

#include "HartPch.hpp"
#include "../Camera/PerspectiveCamera.hpp"
#include "../VertexArray.hpp"
#include "../Shader.hpp"
#include "../Texture2D.hpp"
#include "Colors.hpp"

namespace Hart {
	struct Scene3DData {
		Mat4 viewProjectionMatrix;
	};
	class Renderer3D {
	public:
		static void Init();
		static void DeInit();

		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Mat4& transformationMatrix = Mat4(1.0f));
	private:
		static std::unique_ptr<Scene3DData> s_SceneData;
	};
}