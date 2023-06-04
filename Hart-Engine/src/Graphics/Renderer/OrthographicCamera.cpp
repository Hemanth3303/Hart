#include "HartPch.hpp"
#include "OrthographicCamera.hpp"

namespace Hart {
	namespace Graphics {
		OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) 
			: m_ProjectionMatrix(Maths::Mat4::orthographic(left, right, bottom, top, near, far)) {

		}

		void OrthographicCamera::recalculateViewMatrix() {
			Maths::Mat4 transform = Maths::Mat4::translate(m_Position) * Maths::Mat4::rotate(m_Rotation, Maths::Vec3(0.0f, 0.0f, 1.0f));
			//todo
		}
	}
}
