#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class Group : public Renderable2D {
		public:
			Group(const Maths::Mat4& transformationMatrix);
			~Group();

			void add(Renderable2D* renderable);
			virtual void submit(Renderer2D* renderer) const override;
		private:
			std::vector<const Renderable2D*> m_Renderables;
			Maths::Mat4 m_TransformationMatrix;
		};
	}
}