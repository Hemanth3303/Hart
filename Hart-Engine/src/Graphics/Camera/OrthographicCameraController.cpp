#include "HartPch.hpp"
#include "OrthographicCameraController.hpp"

namespace Hart {
	namespace Graphics {
		OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableCameraRotation)
			: m_AspectRatio(aspectRatio), m_EnableCameraRotation(enableCameraRotation), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel) {

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
			m_CameraMovementSpeed = m_ZoomLevel * m_SpeedMultiplier;
		}

		void OrthographicCameraController::onEvent(Events::Event& e) {
			Events::EventDispatcher eventDispatcher(e);

			eventDispatcher.dispatch<Events::MouseWheelScrolledEvent>(BIND_EVENT_FUNC(OrthographicCameraController::onMouseWheelScrolled));
			eventDispatcher.dispatch<Events::WindowResizedEvent>(BIND_EVENT_FUNC(OrthographicCameraController::onWindowResized));
		}

		void OrthographicCameraController::setInputKeys(Inputs::KeyCode leftKey, Inputs::KeyCode rightKey, Inputs::KeyCode upKey, Inputs::KeyCode downKey, Inputs::KeyCode leftRotateKey, Inputs::KeyCode rightRotateKey) {
			m_LeftKey = leftKey;
			m_RightKey = rightKey;
			m_UpKey = upKey;
			m_DownKey = downKey;
			m_LeftRotateKey = leftRotateKey;
			m_RightRotateKey = rightRotateKey;
		}

		bool OrthographicCameraController::onMouseWheelScrolled(Events::MouseWheelScrolledEvent& e) {
			m_ZoomLevel -= e.getYOffset() * 0.25f;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
			m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			return true;
		}
		
		bool OrthographicCameraController::onWindowResized(Events::WindowResizedEvent& e) {
			m_AspectRatio = static_cast<float>(e.getWidth()) / static_cast<float>(e.getHeight());
			m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			return true;
		}
	}
}