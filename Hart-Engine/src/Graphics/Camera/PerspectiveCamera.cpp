#include "HartPch.hpp"
#include "PerspectiveCamera.hpp"
#include "Maths/MathFunctions.hpp"

namespace Hart {
	PerspectiveCamera::PerspectiveCamera(float fovD, float aspectRatio, float near, float far)
		: m_ProjectionMatrix(Mat4::Perspective(fovD, aspectRatio, near, far)), m_ViewMatrix(1.0f) {

		m_ViewMatrix = Mat4::LookAt(m_Position, Vec3::Add(m_Position, m_Front), m_WorldUp);
		m_ViewProjectionMatrix = Mat4::Multiply(m_ProjectionMatrix, m_ViewMatrix);
	}

	PerspectiveCamera::~PerspectiveCamera() {
	}

	void PerspectiveCamera::setProjection(float fovD, float aspectRatio, float near, float far) {
		m_ProjectionMatrix = Mat4::Perspective(fovD, aspectRatio, near, far);
		m_ViewProjectionMatrix = Mat4::Multiply(m_ProjectionMatrix, m_ViewMatrix);
	}

	void PerspectiveCamera::recalculateViewMatrix() {
		m_Front.x = static_cast<float>(Hart::cosD(m_Rotation.x) * Hart::cosD(m_Rotation.y));
		m_Front.y = static_cast<float>(Hart::sinD(m_Rotation.y));
		m_Front.z = static_cast<float>(Hart::sinD(m_Rotation.x) * Hart::cosD(m_Rotation.y));

		m_Front = Vec3::GetNormal(m_Front);

		m_ViewMatrix = Mat4::LookAt(m_Position, Vec3::Add(m_Position, m_Front), m_WorldUp);
		m_ViewProjectionMatrix = Mat4::Multiply(m_ProjectionMatrix, m_ViewMatrix);
	}
}
