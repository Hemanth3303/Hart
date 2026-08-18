#pragma once

#include "Graphics/Camera/PerspectiveCamera.hpp"
#include "Graphics/VertexArray.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Texture2D.hpp"
#include "Graphics/Colors.hpp"

namespace Hart {

	class Renderer3D {
	public:
		static void Init();
		static void DeInit();

		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const Mat4& transformationMatrix = Mat4(1.0f));
	};
}
