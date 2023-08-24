#pragma once

#include "HartPch.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4.hpp"

namespace Hart {
	// 2D orthographic camera
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

		void setProjection(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

		inline void setPosition(const Vec3& position) { m_Position = position; recalculateViewMatrix(); }
		// Rotation along Z-axis only
		// Provide angle in degrees
		inline void setRotation(float rotationD) { m_RotationD = rotationD; recalculateViewMatrix(); }

		inline const Vec3& getPosition() const { return m_Position; }
		inline const float& getRotation() const { return m_RotationD; }
		inline const Mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const Mat4& getViewMatrix() const { return m_ViewMatrix; }
		inline const Mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void recalculateViewMatrix();
	private:
		Mat4 m_ProjectionMatrix;
		Mat4 m_ViewMatrix;
		Mat4 m_ViewProjectionMatrix;

		Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_RotationD = 0.0f;
	};
}