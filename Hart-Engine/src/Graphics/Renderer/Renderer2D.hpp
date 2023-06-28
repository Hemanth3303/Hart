#pragma once

#include "HartPch.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"
#include "../Primitives/VertexBuffer.hpp"
#include "../Primitives/IndexBuffer.hpp"
#include "../Primitives/VertexArray.hpp"
#include "../Primitives/Shader.hpp"
#include "../Primitives/Texture2D.hpp"
#include "../Camera/OrthographicCamera.hpp"
#include "RenderCommand.hpp"

namespace Hart {
	namespace Graphics {
		struct Scene2DData {
		public:
			std::shared_ptr<VertexArray> vertexArray;
			std::shared_ptr<Shader> shader;
		};

		class Renderer2D {
		public:
			static void Init();
			static void DeInit();

			static void BeginScene(OrthographicCamera& camera, const std::shared_ptr<Shader>& sceneShader);
			static void EndScene();

			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color);
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);

			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color);
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color);

			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f));
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f));

			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f));
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f));
		private:
			static std::unique_ptr<Scene2DData> s_SceneData;
		};
	}
}