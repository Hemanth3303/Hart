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
		struct OrthographicCameraBounds {
		public:
			float left, right, top, bottom;
		public:
			OrthographicCameraBounds(float left, float right, float bottom, float top);

			inline const float getWidth() const { return right - left; }
			inline const float getHeight() const { return top - bottom; }
		};

		// Base class for OrthographicCameraControllers
		class OrthographicCameraController {
		public:
			OrthographicCameraController(float width, float height, bool enableCameraRotation = false);
			virtual ~OrthographicCameraController();

			virtual void update(float deltaTime) = 0;
			virtual void onEvent(Events::Event& e) = 0;

			void setMovementKeys(Inputs::KeyCode leftKey, Inputs::KeyCode rightKey, Inputs::KeyCode upKey, Inputs::KeyCode downKey);
			void setRotationKeys(Inputs::KeyCode leftRotateKey, Inputs::KeyCode rightRotateKey);
			void setAllInputKeys(Inputs::KeyCode leftKey, Inputs::KeyCode rightKey, Inputs::KeyCode upKey, Inputs::KeyCode downKey, Inputs::KeyCode leftRotateKey, Inputs::KeyCode rightRotateKey);

			inline OrthographicCamera& getCamera() { return m_Camera; }
			inline const OrthographicCamera& getCamera() const { return m_Camera; }
			inline const float getZoomLevel() const { return m_ZoomLevel; }
			inline const OrthographicCameraBounds& getBounds() const { return m_Bounds; }
		protected:
			float m_Width, m_Height;
			float m_AspectRatio;
			float m_ZoomLevel = 1.0f;
			bool m_EnableCameraRotation;
			OrthographicCameraBounds m_Bounds;
			OrthographicCamera m_Camera;

			Inputs::KeyCode m_LeftKey = Inputs::KeyCode::ArrowLeft;
			Inputs::KeyCode m_RightKey = Inputs::KeyCode::ArrowRight;
			Inputs::KeyCode m_UpKey = Inputs::KeyCode::ArrowUp;
			Inputs::KeyCode m_DownKey = Inputs::KeyCode::ArrowDown;
			Inputs::KeyCode m_LeftRotateKey = Inputs::KeyCode::N;
			Inputs::KeyCode m_RightRotateKey = Inputs::KeyCode::M;
		};
	}
}