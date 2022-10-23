#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class Group : public Renderable2D {
		public:
			Group(const Maths::Mat4& transform);
			void add(std::shared_ptr<Renderable2D> renderable2d);
			void submit(Renderer2D* renderer2d) const override;
		private:
			std::vector<std::shared_ptr<Renderable2D>> m_Renderables;
			Maths::Mat4 m_TransformationMatrix;
		};
	}
}