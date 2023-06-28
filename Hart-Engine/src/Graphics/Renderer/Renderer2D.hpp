#pragma once

#include "HartPch.hpp"
#include "../Camera/OrthographicCamera.hpp"

namespace Hart {
	namespace Graphics {
		class Renderer2D {
		public:
			static void Init();
			static void DeInit();

			static void BeginScene(OrthographicCamera& camera);
			static void EndScene();

			static void DrawQuad();
		};
	}
}