#include "HartPch.hpp"
#include "OrthographicCamera.hpp"

namespace Hart {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
		: m_ProjectionMatrix(Mat4::Orthographic(left, right, bottom, top, near, far)), m_ViewMatrix(1.0f) {

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float near, float far) {
		m_ProjectionMatrix = Mat4::Orthographic(left, right, bottom, top, near, far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::recalculateViewMatrix() {
		Mat4 transform = Mat4::Translate(m_Position) * Mat4::Rotate(m_RotationD, Vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = Mat4::Inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
