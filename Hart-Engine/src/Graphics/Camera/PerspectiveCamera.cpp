#include "HartPch.hpp"
#include "PerspectiveCamera.hpp"

namespace Hart {
	PerspectiveCamera::PerspectiveCamera(float fovD, float aspectRatio, float near, float far) 
		: m_ProjectionMatrix(Mat4::Perspective(fovD, aspectRatio, near, far)), m_ViewMatrix(1.0f) {

		m_ViewMatrix = Mat4::LookAt(m_Position, m_Position + m_Front, m_WorldUp);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	PerspectiveCamera::~PerspectiveCamera() {

	}

	void PerspectiveCamera::setProjection(float fovD, float aspectRatio, float near, float far) {
		m_ProjectionMatrix = Mat4::Perspective(fovD, aspectRatio, near, far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::recalculateViewMatrix() {
		m_Front.x = static_cast<float>(Hart::cosD(m_Rotation.x) * Hart::cosD(m_Rotation.y));
		m_Front.y = static_cast<float>(Hart::sinD(m_Rotation.y));
		m_Front.z = static_cast<float>(Hart::sinD(m_Rotation.x) * Hart::cosD(m_Rotation.y));

		m_Front.normalize();

		m_ViewMatrix = Mat4::LookAt(m_Position, m_Position + m_Front, m_WorldUp);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}