#include "HartPch.hpp"
#include "OrthographicCamera.hpp"

namespace Hart {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
		: m_ProjectionMatrix(Mat4::OrthographicProjectionMatrix(left, right, bottom, top, near, far)),
		  m_ViewMatrix(1.0f) {

		m_ViewProjectionMatrix = Mat4::Multiply(m_ProjectionMatrix, m_ViewMatrix);
	}

	OrthographicCamera::~OrthographicCamera() {
	}

	void OrthographicCamera::setProjection(float left, float right, float bottom, float top, float near, float far) {
		m_ProjectionMatrix = Mat4::OrthographicProjectionMatrix(left, right, bottom, top, near, far);
		m_ViewProjectionMatrix = Mat4::Multiply(m_ProjectionMatrix, m_ViewMatrix);
	}

	void OrthographicCamera::recalculateViewMatrix() {
		Mat4 translation = Mat4::Translate(m_Position);
		Mat4 rotation = Mat4::Rotate(m_RotationD, Vec3(0.0f, 0.0f, 1.0f));
		Mat4 transform = Mat4::Multiply(translation, rotation);

		m_ViewMatrix = Mat4::Inverse(transform);
		m_ViewProjectionMatrix = Mat4::Multiply(m_ProjectionMatrix, m_ViewMatrix);
	}
}
