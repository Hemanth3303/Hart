#include "HartPch.hpp"
#include "OrthographicCamera.hpp"

namespace Hart {
	namespace Graphics {
		OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) 
			: m_ProjectionMatrix(Maths::Mat4::orthographic(left, right, bottom, top, near, far)), m_ViewMatrix(1.0f) {

			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float near, float far) {
			m_ProjectionMatrix = Maths::Mat4::orthographic(left, right, bottom, top, near, far);
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		void OrthographicCamera::recalculateViewMatrix() {
			Maths::Mat4 transform = Maths::Mat4::translate(m_Position) * Maths::Mat4::rotate(m_RotationD, Maths::Vec3(0.0f, 0.0f, 1.0f));
			
			m_ViewMatrix = Maths::Mat4::inverse(transform);
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}
	}
}
