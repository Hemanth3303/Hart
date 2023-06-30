#include "HartPch.hpp"
#include "OrthographicCameraController.hpp"

namespace Hart {
	namespace Graphics {

		constexpr float HIDDEN_SPEED_MULTIPLIER = 100.0f;

		OrthographicCameraController::OrthographicCameraController(float width, float height, bool enableCameraRotation)
			: m_Width(width), m_Height(height), m_EnableCameraRotation(enableCameraRotation), m_Camera(-(m_Width * m_ZoomLevel) / 2.0f, (m_Width * m_ZoomLevel) / 2.0f, -(m_Height * m_ZoomLevel) / 2.0f, (m_Height * m_ZoomLevel) / 2.0f) {

		}

		OrthographicCameraController::~OrthographicCameraController() {

		}

		void OrthographicCameraController::update(const float deltaTime) {
			if (Inputs::InputManager::IsKeyPressed(m_LeftKey)) {
				m_CameraPosition.x -= m_CameraMovementSpeed * deltaTime;
			}
			if (Inputs::InputManager::IsKeyPressed(m_RightKey)) {
				m_CameraPosition.x += m_CameraMovementSpeed * deltaTime;
			}
			if (Inputs::InputManager::IsKeyPressed(m_UpKey)) {
				m_CameraPosition.y += m_CameraMovementSpeed * deltaTime;
			}
			if (Inputs::InputManager::IsKeyPressed(m_DownKey)) {
				m_CameraPosition.y -= m_CameraMovementSpeed * deltaTime;
			}

			if (m_EnableCameraRotation) {
				if (Inputs::InputManager::IsKeyPressed(m_LeftRotateKey)) {
					m_CameraRotation += m_CameraRotationSpeed * deltaTime;
				}
				if (Inputs::InputManager::IsKeyPressed(m_RightRotateKey)) {
					m_CameraRotation -= m_CameraRotationSpeed * deltaTime;
				}
				m_Camera.setRotation(m_CameraRotation);
			}

			m_Camera.setPosition(m_CameraPosition);
			m_CameraMovementSpeed = m_ZoomLevel * m_SpeedMultiplier * HIDDEN_SPEED_MULTIPLIER;
		}

		void OrthographicCameraController::onEvent(Events::Event& e) {
			Events::EventDispatcher eventDispatcher(e);

			eventDispatcher.dispatch<Events::MouseWheelScrolledEvent>(BIND_EVENT_FUNC(OrthographicCameraController::onMouseWheelScrolled));
			eventDispatcher.dispatch<Events::WindowResizedEvent>(BIND_EVENT_FUNC(OrthographicCameraController::onWindowResized));
		}

		void OrthographicCameraController::setMovementKeys(Inputs::KeyCode leftKey, Inputs::KeyCode rightKey, Inputs::KeyCode upKey, Inputs::KeyCode downKey) {
			m_LeftKey = leftKey;
			m_RightKey = rightKey;
			m_UpKey = upKey;
			m_DownKey = downKey;
		}

		void OrthographicCameraController::setRotationKeys(Inputs::KeyCode leftRotateKey, Inputs::KeyCode rightRotateKey) {
			m_LeftRotateKey = leftRotateKey;
			m_RightRotateKey = rightRotateKey;
		}

		void OrthographicCameraController::setAllInputKeys(Inputs::KeyCode leftKey, Inputs::KeyCode rightKey, Inputs::KeyCode upKey, Inputs::KeyCode downKey, Inputs::KeyCode leftRotateKey, Inputs::KeyCode rightRotateKey) {
			setMovementKeys(leftKey, rightKey, upKey, downKey);
			setRotationKeys(leftRotateKey, rightKey);
		}

		bool OrthographicCameraController::onMouseWheelScrolled(Events::MouseWheelScrolledEvent& e) {
			m_ZoomLevel -= e.getYOffset() * 0.05f;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.05f);
			m_Camera.setProjection(-(m_Width * m_ZoomLevel) / 2.0f, (m_Width * m_ZoomLevel) / 2.0f, -(m_Height * m_ZoomLevel) / 2.0f, (m_Height * m_ZoomLevel) / 2.0f);
			return true;
		}
		
		bool OrthographicCameraController::onWindowResized(Events::WindowResizedEvent& e) {
			m_Width = static_cast<float>(e.getWidth());
			m_Height = static_cast<float>(e.getHeight());
			m_Camera.setProjection(-(m_Width * m_ZoomLevel) / 2.0f, (m_Width * m_ZoomLevel) / 2.0f, -(m_Height * m_ZoomLevel) / 2.0f, (m_Height * m_ZoomLevel) / 2.0f);
			return true;
		}
	}
}