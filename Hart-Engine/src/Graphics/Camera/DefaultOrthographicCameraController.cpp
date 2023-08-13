#include "HartPch.hpp"
#include "DefaultOrthographicCameraController.hpp"

namespace Hart {
	namespace Graphics {

		DefaultOrthographicCameraController::DefaultOrthographicCameraController(float width, float height, bool enableCameraRotation)
			: OrthographicCameraController(width, height, enableCameraRotation) {

		}

		DefaultOrthographicCameraController::~DefaultOrthographicCameraController() {

		}

		void DefaultOrthographicCameraController::update(const float deltaTime) {
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

		void DefaultOrthographicCameraController::onEvent(Events::Event& e) {
			Events::EventDispatcher eventDispatcher(e);

			eventDispatcher.dispatch<Events::MouseWheelScrolledEvent>(BIND_EVENT_FUNC(DefaultOrthographicCameraController::onMouseWheelScrolled));
			eventDispatcher.dispatch<Events::WindowResizedEvent>(BIND_EVENT_FUNC(DefaultOrthographicCameraController::onWindowResized));
		}

		bool DefaultOrthographicCameraController::onMouseWheelScrolled(Events::MouseWheelScrolledEvent& e) {
			m_ZoomLevel -= e.getYOffset() * 0.05f;
			m_ZoomLevel = std::max(m_ZoomLevel, 0.05f);
			m_Bounds=OrthographicCameraBounds(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			m_Camera.setProjection(m_Bounds.left, m_Bounds.right, m_Bounds.bottom, m_Bounds.top);
			return true;
		}
		
		bool DefaultOrthographicCameraController::onWindowResized(Events::WindowResizedEvent& e) {
			m_Width = static_cast<float>(e.getWidth());
			m_Height = static_cast<float>(e.getHeight());
			m_Bounds = OrthographicCameraBounds(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
			m_Camera.setProjection(m_Bounds.left, m_Bounds.right, m_Bounds.bottom, m_Bounds.top);
			return true;
		}
	}
}