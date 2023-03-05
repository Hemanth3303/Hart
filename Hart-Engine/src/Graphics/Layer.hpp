/*
* Base class for a layer
*/

#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"
#include "Renderer2D.hpp"

namespace Hart {
	namespace Graphics {
		// This class does not take ownership of the renderer, shader or renderables passed to it
		class Layer {
		public:
			virtual ~Layer();
			virtual void add(const Renderable2D* renderable);
			virtual void render();
		protected:
			Layer(Renderer2D* renderer, const Shader& shader, const Maths::Mat4& projectionMatrix);
		protected:
			Renderer2D* m_Renderer;
			std::vector<const Renderable2D*> m_Renderables;
			const Shader& m_Shader;
			Maths::Mat4 m_ProjectionMatrix;
		};
	}
}