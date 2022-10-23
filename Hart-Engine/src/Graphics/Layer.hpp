#pragma once

#include "HartPch.hpp"
#include "Renderer2D.hpp"
#include "Renderable2D.hpp"
#include "Maths/Maths.hpp"

namespace Hart {
	namespace Graphics {
		class Layer {
		public:
			virtual ~Layer();
			virtual void add(std::shared_ptr<Renderable2D> renderable2d);
			virtual void render();
		protected:
			Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, const Maths::Mat4& projectionMatrix);
		protected:
			std::shared_ptr<Renderer2D> m_Renderer;
			std::vector <std::shared_ptr<Renderable2D>> m_Renderables;
			std::shared_ptr<Shader> m_Shader;
			Maths::Mat4 m_ProjectionMatrix;
		};
	}
}