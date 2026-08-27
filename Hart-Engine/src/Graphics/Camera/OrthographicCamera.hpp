#pragma once

#include "Maths/Vec3.hpp"
#include "Maths/Mat4.hpp"
#include "Maths/MathFunctions.hpp"

namespace Hart {
	// 2D orthographic camera
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);
		~OrthographicCamera();

		void setProjection(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);
		float getScreenYAxisUpSign();

		inline void setPosition(const Vec3& position) {
			m_Position = position;
			recalculateViewMatrix();
		}
		// Rotation along Z-axis only
		// Provide angle in degrees
		inline void setRotation(float rotationD) {
			m_RotationD = rotationD;
			recalculateViewMatrix();
		}

		inline const Vec3& getPosition() const { return m_Position; }
		inline const float& getRotation() const { return m_RotationD; }
		inline const Mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const Mat4& getViewMatrix() const { return m_ViewMatrix; }
		inline const Mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		inline float getWidth() const { return Hart::absoluteValue(m_Right - m_Left); }
		inline float getHeight() const { return Hart::absoluteValue(m_Top - m_Bottom); }

	private:
		void recalculateViewMatrix();

	private:
		float m_Left = 0.0f;
		float m_Right = 0.0f;
		float m_Bottom = 0.0f;
		float m_Top = 0.0f;

		Mat4 m_ProjectionMatrix;
		Mat4 m_ViewMatrix;
		Mat4 m_ViewProjectionMatrix;

		Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_RotationD = 0.0f;
	};
}
