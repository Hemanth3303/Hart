#pragma once

#include "HartPch.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4.hpp"

namespace Hart {
	namespace Graphics {
		// 2D orthographic camera
		class OrthographicCamera {
		public:
			OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

			void setProjection(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

			inline void setPosition(const Maths::Vec3& position) { m_Position = position; recalculateViewMatrix(); }
			// Rotation along Z-axis only
			// Provide angle in degrees
			inline void setRotation(float rotationD) { m_RotationD = rotationD; recalculateViewMatrix(); }

			inline const Maths::Vec3& getPosition() const { return m_Position; }
			inline const float& getRotation() const { return m_RotationD; }
			inline const Maths::Mat4& getProjectionMatrix() const { return m_ProjectionMatrix; }
			inline const Maths::Mat4& getViewMatrix() const { return m_ViewMatrix; }
			inline const Maths::Mat4& getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		private:
			void recalculateViewMatrix();
		private:
			Maths::Mat4 m_ProjectionMatrix;
			Maths::Mat4 m_ViewMatrix;
			Maths::Mat4 m_ViewProjectionMatrix;

			Maths::Vec3 m_Position = { 0.0f, 0.0f, 0.0f };
			float m_RotationD = 0.0f;
		};
	}
}