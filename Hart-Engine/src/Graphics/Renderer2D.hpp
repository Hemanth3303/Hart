/*
* abstract class for 2d renderers
*/

#pragma once

#include "HartPch.hpp"
#include "Maths/Maths.hpp"

#include "glad/glad.h"

namespace Hart {
	namespace Graphics {

		class Renderable2D;

		class Renderer2D {
		public:
			virtual void begin() {}
			
			//adds to render queue
			virtual void submit(const Renderable2D* renderable2d) = 0;
			//draw the elements in the render queue
			virtual void flush() = 0;

			virtual void end() {}
		protected:
			std::vector<Maths::Mat4> m_TransformationStack;
			const Maths::Mat4* m_TransformationBack;
		protected:
			Renderer2D();
		public:
			//adds a new matrix to the transformation stack
			//if override is true, removes the effect of the previous matrices in the transformation stack
			void push(const Maths::Mat4& matrix, bool override = false);
			//removes the last transformation matrix from the the transformation stack
			void pop();
		};
	}
}