/*
* Base class for 2d renderers
*/

#pragma once

#include "HartPch.hpp"
#include "Renderable2D.hpp"

namespace Hart {
	namespace Graphics {
		class Renderer2D {
		public:
			virtual void begin() {}
			
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;

			virtual void end() {}

			void pushTransformationMatrix(const Maths::Mat4& matrix, bool override = false) {
				if (override) {
					m_TransformationStack.push_back(matrix);
				}
				else {
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
				}
				m_TransformationBack = &m_TransformationStack.back();
			}

			void popTransformationMatrix() {
				if (m_TransformationStack.size() > 1) {
					m_TransformationStack.pop_back();
				}
				m_TransformationBack = &m_TransformationStack.back();
			}
		protected:
			std::vector<Maths::Mat4> m_TransformationStack;
			const Maths::Mat4* m_TransformationBack;
		protected:
			Renderer2D() {
				m_TransformationStack.push_back(Maths::Mat4::indentity());
				m_TransformationBack = &m_TransformationStack.back();
			}
		};
	}
}