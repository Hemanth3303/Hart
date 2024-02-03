#pragma once

#include "HartPch.hpp"
#include "OrthographicCameraController.hpp"

namespace Hart {
	// default 2d camera controller
	class DefaultOrthographicCameraController : public OrthographicCameraController {
	public:
		DefaultOrthographicCameraController(float width, float height, bool enableCameraRotation = false);
		~DefaultOrthographicCameraController();

		void update(const float deltaTime) override;
		void resize(const float width, const float height);
		void onEvent(Event& e) override;

		// default is 45.0f
		inline void setRotationSpeed(const float rotationSpeed) { m_CameraRotationSpeed = rotationSpeed; }
		// default is 5.0f
		inline void setMovementSpeed(const float movementSpeed) { m_SpeedMultiplier = movementSpeed; }
	private:
		bool onMouseWheelScrolled(MouseWheelScrolledEvent& e);
		bool onWindowResized(WindowResizedEvent& e);
	private:

		float m_CameraMovementSpeed = m_ZoomLevel;
		float m_SpeedMultiplier = 5.0f;
		float m_CameraRotationSpeed = 45.0f;
		Vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
	};
}