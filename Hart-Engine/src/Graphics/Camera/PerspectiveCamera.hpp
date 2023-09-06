#pragma once

#include "HartPch.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Mat4.hpp"

namespace Hart {
	// 3D perspective camera
	class PerspectiveCamera {
	public:
		PerspectiveCamera(float fovD, float aspectRatio, float near = 0.1f, float far = 100.0f);
		~PerspectiveCamera();

		void setProjection(float fovD, float aspectRatio, float near = 0.1f, float far = 100.0f);

		inline void setPosition(const Vec3& position) { m_Position = position; recalculateViewMatrix(); }
		inline void setFront(const Vec3& front) { m_Front = front; recalculateViewMatrix(); }
		inline void setWorldUp(const Vec3& worldUp) { m_WorldUp = worldUp; recalculateViewMatrix(); }
		inline void setRotation(const Vec3& rotation) { m_Rotation = rotation; recalculateViewMatrix(); }

		inline const Vec3& getPosition() const { return m_Position; }
		inline const Vec3& getFront() const { return m_Front; }
		inline const Vec3& getWorldUp() const { return m_WorldUp; }
		inline const Vec3& getRotation() const { return m_Rotation; }
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
		Vec3 m_Front = { 0.0f, 0.0f, 0.0f };
		Vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

		Vec3 m_Rotation = { -90.0f, 0.0f, 0.0f };
	};
}