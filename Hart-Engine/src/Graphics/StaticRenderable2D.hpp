/*
* This renderable is static, unable to apply transformations on it
*/

#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class StaticRenderable2D : public Renderable2D {
		public:
			StaticRenderable2D(const Maths::Vec3& position, const Maths::Vec2& size, const Maths::Vec4& color, std::shared_ptr<Shader> shader);
			virtual ~StaticRenderable2D();

			Shader* getShader() const { return m_Shader.get(); }
		private:
			std::shared_ptr<Shader> m_Shader;
		};
	}
}