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

			// Quads

			// Draws a quad with color
			// color is in rgba(0 to 1) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color);

			// Draws a rotated quad with color
			// color is in rgba(0 to 1) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& color);

			// Draws a quad with texture and optional tinting color and tiling factor
			// color is in rgba(0 to 1) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = White, float tilingFactor = 1.0f);

			// Draws a rotated quad with texture and optional tinting color and tiling factor
			// color is in rgba(0 to 1) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Maths::Vec4& textureTint = White, float tilingFactor = 1.0f);

			// Draws a quad with texture and optional tinting color
			// The texture is a part of the provided spritesheet, indexed using a Maths::Vec2
			// The top left is considered as (0, 0) and bottom right is (n-1, n-1), where n is number of sprites in spritesheet
			// color is in rgba(0 to 1) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, const std::shared_ptr<SpriteSheet>& spriteSheet, const Maths::Vec2& subTextureIndex, const Maths::Vec4& textureTint = White);

			// Draws a rotated quad with texture and optional tinting color
			// The texture is a part of the provided spritesheet, indexed using a Maths::Vec2
			// The top left is considered as (0, 0) and bottom right is (n-1, n-1), where n is number of sprites in spritesheet
			// color is in rgba(0 to 1) format
			static void DrawQuad(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const std::shared_ptr<SpriteSheet>& spriteSheet, const Maths::Vec2& subTextureIndex, const Maths::Vec4& textureTint = White);

			// Lines

			// changes the width of every line in a a scene
			static void SetLineWidth(float width);

			static void DrawLine(const Maths::Vec3& startPosition, const Maths::Vec3& endPosition, const Maths::Vec4& color = White);

			static void ResetStats();
			static std::uint32_t GetNumberOfDrawCalls();
			static std::uint32_t GetNumberOfQuads();
			static std::uint32_t GetNumberOfVertices();
			static std::uint32_t GetNumberOfIndices();

		private:
			static void BeginBatch();
			static void Flush();

			static void AddNewQuadVertex(const Maths::Vec3& position, const Maths::Vec2& size, float angleD, const Maths::Vec4& quadColor, float textureIndex, float tiliingFactor);
			static void AddNewLineVertex(const Maths::Vec3& startPosition, const Maths::Vec3& endPosition, const Maths::Vec4& color);
		};
	}
}