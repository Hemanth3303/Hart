#pragma once

#include "HartPch.hpp"
#include "OrthographicCamera.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/EventDispatcher.hpp"
#include "Inputs/InputManager.hpp"

namespace Hart {
	namespace Graphics {
		// default 2d camera controller
		class OrthographicCameraController {
		public:
			OrthographicCameraController(float width, float height, bool enableCameraRotation = false);
			~OrthographicCameraController();

			void update(const float deltaTime);
			void onEvent(Events::Event& e);
			void setInputKeys(Inputs::KeyCode leftKey, Inputs::KeyCode rightKey, Inputs::KeyCode upKey, Inputs::KeyCode downKey, Inputs::KeyCode leftRotateKey, Inputs::KeyCode rightRotateKey);

			inline OrthographicCamera& getCamera() { return m_Camera; }
			inline const OrthographicCamera& getCamera() const { return m_Camera; }
			inline const float getRotationSpeed() const { return m_CameraRotationSpeed; }
			inline const float ZoomLevel() const { return m_ZoomLevel; }

			// default is 45.0f
			inline void setRotationSpeed(const float rotationSpeed) { m_CameraRotationSpeed = rotationSpeed; }
			// default is 10.0f
			inline void setMovementSpeed(const float movementSpeed) { m_SpeedMultiplier = movementSpeed; }
		private:
			bool onMouseWheelScrolled(Events::MouseWheelScrolledEvent& e);
			bool onWindowResized(Events::WindowResizedEvent& e);
		private:
			float m_Width, m_Height;
			float m_ZoomLevel = 1.0f;
			bool m_EnableCameraRotation;
			OrthographicCamera m_Camera;

			float m_CameraMovementSpeed = m_ZoomLevel;
			float m_SpeedMultiplier = 10.0f;
			float m_CameraRotationSpeed = 45.0f;
			Maths::Vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
			float m_CameraRotation = 0.0f;

			Inputs::KeyCode m_LeftKey = Inputs::KeyCode::ArrowLeft;
			Inputs::KeyCode m_RightKey = Inputs::KeyCode::ArrowRight;
			Inputs::KeyCode m_UpKey = Inputs::KeyCode::ArrowUp;
			Inputs::KeyCode m_DownKey = Inputs::KeyCode::ArrowDown;
			Inputs::KeyCode m_LeftRotateKey = Inputs::KeyCode::N;
			Inputs::KeyCode m_RightRotateKey = Inputs::KeyCode::M;
		};
	}
}