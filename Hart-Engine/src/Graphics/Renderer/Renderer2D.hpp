#pragma once

#include "HartPch.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "../Texture2D.hpp"
#include "../SpriteSheet.hpp"
#include "../Camera/OrthographicCamera.hpp"
#include "Colors.hpp"

namespace Hart {
	class Renderer2D {
	public:
		static void Init();
		static void DeInit();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		// Quads

		// Draws a quad with color
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Vec3& position, const Vec2& size, const Vec4& color);

		// Draws a rotated quad with color
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Vec3& position, const Vec2& size, float angleD, const Vec4& color);

		// Draws a quad with texture and optional tinting color and tiling factor
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint = White, float tilingFactor = 1.0f);

		// Draws a rotated quad with texture and optional tinting color and tiling factor
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Vec3& position, const Vec2& size, float angleD, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint = White, float tilingFactor = 1.0f);

		// Draws a quad with texture and optional tinting color
		// The texture is a part of the provided spritesheet, indexed using a Vec2
		// The top left is considered as (0, 0) and bottom right is (n-1, n-1), where n is number of sprites in spritesheet
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Vec3& position, const Vec2& size, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint = White);

		// Draws a rotated quad with texture and optional tinting color
		// The texture is a part of the provided spritesheet, indexed using a Vec2
		// The top left is considered as (0, 0) and bottom right is (n-1, n-1), where n is number of sprites in spritesheet
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Vec3& position, const Vec2& size, float angleD, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint = White);

		// Draws a quad with given transform and color
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Mat4& transform, const Vec4& color);

		// Draws a quad with given transform, texture and optional tinting color and tiling factor
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Mat4& transform, const std::shared_ptr<Texture2D>& texture, const Vec4& textureTint = White, float tilingFactor = 1.0f);

		// Draws a quad with given transform, texture and optional tinting color
		// The texture is a part of the provided spritesheet, indexed using a Vec2
		// The top left is considered as (0, 0) and bottom right is (n-1, n-1), where n is number of sprites in spritesheet
		// color is in rgba(0 to 1) format
		static void DrawQuad(const Mat4& transform, const std::shared_ptr<SpriteSheet>& spriteSheet, const Vec2& subTextureIndex, const Vec4& textureTint = White);

		// Lines

		static void DrawLine(const Vec3& startPosition, const Vec3& endPosition, const Vec4& color = White, const float thickness = 1.0f);

		// Text

		static void DrawText(const std::string& text, const Vec3& position, float size, const Vec4& color = White);

		static void DrawText(const std::string& text, const Vec3& position, float size, float angleD, const Vec4& color = White);

		static void DrawText(const std::string& text, const Mat4& transform, const Vec4& color = White);

		static void ResetStats();
		static std::uint32_t GetNumberOfDrawCalls();
		static std::uint32_t GetNumberOfQuads();
		static std::uint32_t GetNumberOfQuadVertices();
		static std::uint32_t GetNumberOfQuadIndices();
	private:
		static void BeginBatch();
		static void Flush();

		static const float CalculateTextureIndex(const std::shared_ptr<Texture2D>& texture);

		static void AddNewQuadVertex(const Mat4& transform, const Vec4& color, float textureIndex, float tiliingFactor);
	};
}