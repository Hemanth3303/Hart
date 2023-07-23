#pragma once

#include "HartPch.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Maths/Mat4.hpp"
#include "../Shader.hpp"
#include "../Texture2D.hpp"
#include "../SpriteSheet.hpp"
#include "../Camera/OrthographicCamera.hpp"
#include "Colors.hpp"

namespace Hart {
	namespace Graphics {
		class Renderer2D {
		public:
			static void Init();
			static void DeInit();

			static void BeginScene(OrthographicCamera& camera);
			static void EndScene();

			static void SetCustomShader(const std::shared_ptr<Shader>& shader);
			// removes custom shader and goes back to default shader
			static void UnsetCustomShader();

			// Draws a quad with color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);

			// Draws a rotated quad with color
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color);

			// Draws a quad with texture and optional tinting color and tiling factor
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = White, float tilingFactor = 1.0f);

			// Draws a rotated quad with texture and optional tinting color and tiling factor
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = White, float tilingFactor = 1.0f);

			// Draws a quad with texture and optional tinting color
			// The texture is a part of the provided spritesheet, indexed using a Maths::Vec2
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<SpriteSheet>& spriteSheet, const Maths::Vec2& subTextureIndex, const Maths::Vec4& textureTint = White);

			// Draws a rotated quad with texture and optional tinting color
			// The texture is a part of the provided spritesheet, indexed using a Maths::Vec2
			// color is in rgba(0 to 255) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<SpriteSheet>& spriteSheet, const Maths::Vec2& subTextureIndex, const Maths::Vec4& textureTint = White);

			static void ResetStats();
			static std::uint32_t GetNumberOfDrawCalls();
			static std::uint32_t GetNumberOfQuads();
			static std::uint32_t GetNumberOfVertices();
			static std::uint32_t GetNumberOfIndices();

		private:
			static void BeginBatch();
			static void Flush();

			static void UpdateVertexBufferPtr(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& quadColor, float textureIndex, float tiliingFactor);
		};
	}
}