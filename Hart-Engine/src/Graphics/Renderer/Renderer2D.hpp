#pragma once

#include "HartPch.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"
#include "../Primitives/Texture2D.hpp"
#include "../Camera/OrthographicCamera.hpp"
#include "RenderCommand.hpp"
#include "Colors.hpp"

namespace Hart {
	namespace Graphics {
		class Renderer2D {
		public:
			static void Init();
			static void DeInit();

			static void BeginScene(OrthographicCamera& camera);
			static void BeginScene(OrthographicCamera& camera, const std::shared_ptr<Shader>& sceneShader);
			static void EndScene();

			// Draws a quad with color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const Maths::Vec4& color);
			// Draws a quad with color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);

			// Draws a rotated quad with color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color);
			// Draws a rotated quad with color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color);

			// Draws a quad with texture and optional tinting color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f), float textureTilingFactor = 1.0f);
			// Draws a quad with texture and optional tinting color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f), float textureTilingFactor = 1.0f);

			// Draws a rotated quad with texture and optional tinting color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec2& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f), float textureTilingFactor = 1.0f);
			// Draws a rotated quad with texture and optional tinting color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = Maths::Vec4(255.0f), float textureTilingFactor = 1.0f);
		private:
			static void BeginSceneImplementation();
		};
	}
}