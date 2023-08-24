#pragma once

#include "HartPch.hpp"

#include "OrthographicCamera.hpp"
#include "Events/Event.hpp"
#include "Events/WindowEvents.hpp"
#include "Events/MouseEvents.hpp"
#include "Events/EventDispatcher.hpp"
#include "Inputs/InputManager.hpp"

namespace Hart {
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
		virtual void onEvent(Event& e) = 0;

		void setMovementKeys(KeyCode leftKey, KeyCode rightKey, KeyCode upKey, KeyCode downKey);
		void setRotationKeys(KeyCode leftRotateKey, KeyCode rightRotateKey);
		void setAllInputKeys(KeyCode leftKey, KeyCode rightKey, KeyCode upKey, KeyCode downKey, KeyCode leftRotateKey, KeyCode rightRotateKey);

		inline OrthographicCamera& getCamera() { return m_Camera; }
		inline const OrthographicCamera& getCamera() const { return m_Camera; }
		inline const float getAspectRatio() const { return m_AspectRatio; }
		inline const float getZoomLevel() const { return m_ZoomLevel; }
		inline const OrthographicCameraBounds& getBounds() const { return m_Bounds; }
	protected:
		float m_Width, m_Height;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_EnableCameraRotation;
		OrthographicCameraBounds m_Bounds;
		OrthographicCamera m_Camera;

		KeyCode m_LeftKey = KeyCode::ArrowLeft;
		KeyCode m_RightKey = KeyCode::ArrowRight;
		KeyCode m_UpKey = KeyCode::ArrowUp;
		KeyCode m_DownKey = KeyCode::ArrowDown;
		KeyCode m_LeftRotateKey = KeyCode::N;
		KeyCode m_RightRotateKey = KeyCode::M;
	};
}