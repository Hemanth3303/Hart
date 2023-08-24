#include "HartPch.hpp"
#include "OrthographicCameraController.hpp"

namespace Hart {
	OrthographicCameraBounds::OrthographicCameraBounds(float left, float right, float bottom, float top) {
		this->left = left;
		this->right = right;
		this->bottom = bottom;
		this->top = top;
	}

	OrthographicCameraController::OrthographicCameraController(float width, float height, bool enableCameraRotation)
		: m_Width(width), m_Height(height), m_AspectRatio(m_Width / m_Height), m_EnableCameraRotation(enableCameraRotation), m_Bounds(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Camera(m_Bounds.left, m_Bounds.right, m_Bounds.bottom, m_Bounds.top) {

	}

	OrthographicCameraController::~OrthographicCameraController() {

	}

	void OrthographicCameraController::setMovementKeys(KeyCode leftKey, KeyCode rightKey, KeyCode upKey, KeyCode downKey) {
		m_LeftKey = leftKey;
		m_RightKey = rightKey;
		m_UpKey = upKey;
		m_DownKey = downKey;
	}

	void OrthographicCameraController::setRotationKeys(KeyCode leftRotateKey, KeyCode rightRotateKey) {
		m_LeftRotateKey = leftRotateKey;
		m_RightRotateKey = rightRotateKey;
	}

	void OrthographicCameraController::setAllInputKeys(KeyCode leftKey, KeyCode rightKey, KeyCode upKey, KeyCode downKey, KeyCode leftRotateKey, KeyCode rightRotateKey) {
		setMovementKeys(leftKey, rightKey, upKey, downKey);
		setRotationKeys(leftRotateKey, rightKey);
	}
}