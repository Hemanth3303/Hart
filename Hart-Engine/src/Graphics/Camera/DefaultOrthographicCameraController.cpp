#include "HartPch.hpp"
#include "DefaultOrthographicCameraController.hpp"

namespace Hart {
	DefaultOrthographicCameraController::DefaultOrthographicCameraController(float width, float height, bool enableCameraRotation)
		: OrthographicCameraController(width, height, enableCameraRotation) {

		m_Bounds = OrthographicCameraBounds(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.setProjection(m_Bounds.left, m_Bounds.right, m_Bounds.bottom, m_Bounds.top);
	}

	DefaultOrthographicCameraController::~DefaultOrthographicCameraController() {

	}

	void DefaultOrthographicCameraController::update(const float deltaTime) {
		if (InputManager::IsKeyPressed(m_LeftKey)) {
			m_CameraPosition.x -= m_CameraMovementSpeed * deltaTime;
		}
		if (InputManager::IsKeyPressed(m_RightKey)) {
			m_CameraPosition.x += m_CameraMovementSpeed * deltaTime;
		}
		if (InputManager::IsKeyPressed(m_UpKey)) {
			m_CameraPosition.y += m_CameraMovementSpeed * deltaTime;
		}
		if (InputManager::IsKeyPressed(m_DownKey)) {
			m_CameraPosition.y -= m_CameraMovementSpeed * deltaTime;
		}

		if (m_EnableCameraRotation) {
			if (InputManager::IsKeyPressed(m_LeftRotateKey)) {
				m_CameraRotation += m_CameraRotationSpeed * deltaTime;
			}
			if (InputManager::IsKeyPressed(m_RightRotateKey)) {
				m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
			}
			m_Camera.setRotation(m_CameraRotation);
		}

		m_Camera.setPosition(m_CameraPosition);
		m_CameraMovementSpeed = m_ZoomLevel * m_SpeedMultiplier;
	}

	void DefaultOrthographicCameraController::resize(const float width, const float height) {
		m_Width = width;
		m_Height = height;
		m_AspectRatio = (width / height);
	}

	void DefaultOrthographicCameraController::onEvent(Event& e) {
		EventDispatcher eventDispatcher(e);

		eventDispatcher.dispatch<MouseWheelScrolledEvent>(BIND_EVENT_FUNC(DefaultOrthographicCameraController::onMouseWheelScrolled));
		eventDispatcher.dispatch<WindowResizedEvent>(BIND_EVENT_FUNC(DefaultOrthographicCameraController::onWindowResized));
	}

	bool DefaultOrthographicCameraController::onMouseWheelScrolled(MouseWheelScrolledEvent& e) {
		m_ZoomLevel -= e.getYOffset() * 0.05f;
		m_ZoomLevel = std::clamp(m_ZoomLevel, 0.05f, 5.0f);
		m_Bounds = OrthographicCameraBounds(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.setProjection(m_Bounds.left, m_Bounds.right, m_Bounds.bottom, m_Bounds.top);
		return true;
	}

	bool DefaultOrthographicCameraController::onWindowResized(WindowResizedEvent& e) {
		resize(static_cast<float>(e.getWidth()), static_cast<float>(e.getHeight()));
		m_Bounds = OrthographicCameraBounds(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		m_Camera.setProjection(m_Bounds.left, m_Bounds.right, m_Bounds.bottom, m_Bounds.top);
		return true;
	}
}