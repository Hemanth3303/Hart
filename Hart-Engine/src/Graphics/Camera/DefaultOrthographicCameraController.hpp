#pragma once

#include "HartPch.hpp"
#include "OrthographicCameraController.hpp"

namespace Hart {
	namespace Graphics {
		// default 2d camera controller
		class DefaultOrthographicCameraController : public OrthographicCameraController {
		public:
			DefaultOrthographicCameraController(float width, float height, bool enableCameraRotation = false);
			~DefaultOrthographicCameraController();

			void update(const float deltaTime) override;
			void onEvent(Events::Event& e) override;

			// default is 45.0f
			inline void setRotationSpeed(const float rotationSpeed) { m_CameraRotationSpeed = rotationSpeed; }
			// default is 10.0f
			inline void setMovementSpeed(const float movementSpeed) { m_SpeedMultiplier = movementSpeed; }
		private:
			bool onMouseWheelScrolled(Events::MouseWheelScrolledEvent& e);
			bool onWindowResized(Events::WindowResizedEvent& e);
		private:

			float m_CameraMovementSpeed = m_ZoomLevel;
			float m_SpeedMultiplier = 10.0f;
			float m_CameraRotationSpeed = 45.0f;
			Maths::Vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
			float m_CameraRotation = 0.0f;
		};
	}
}