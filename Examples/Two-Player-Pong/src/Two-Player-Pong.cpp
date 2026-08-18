// Example Game: Two player controlled pong game

#include "Core/EntryPoint.hpp"
#include "Hart.hpp"

class GameLayer : public Hart::Layer {
public:
	GameLayer(const std::string& name = "GameLayer")
		: Layer(name) {
	}
	~GameLayer() {
	}

	virtual void onAttach() override {
		m_CameraController = std::make_shared<Hart::DefaultOrthographicCameraController>(640.0f, 480.0f, false);
		// disabling camera movement
		m_CameraController->setMovementSpeed(0.0f);

		m_Font = std::make_shared<Hart::Font>("res/fonts/Roboto-Regular.ttf");
		Hart::Renderer2D::SetFont(m_Font);
	}
	virtual void onDetach() override {
	}

	virtual void onEvent(Hart::Event& e) override {
	}

	virtual void update(const float deltaTime) override {
		m_CameraController->update(deltaTime);

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::W)) {
			m_PlayerOnePos.y += PLAYER_SPEED * deltaTime;
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::S)) {
			m_PlayerOnePos.y -= PLAYER_SPEED * deltaTime;
		}

		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::ArrowUp)) {
			m_PlayerTwoPos.y += PLAYER_SPEED * deltaTime;
		}
		if (Hart::InputManager::IsKeyPressed(Hart::KeyCode::ArrowDown)) {
			m_PlayerTwoPos.y -= PLAYER_SPEED * deltaTime;
		}

		float playerHalfHeight = m_PlayerSize.y / 2.0f;
		m_PlayerOnePos.y = Hart::clamp(m_PlayerOnePos.y, -1.0f + playerHalfHeight, 1.0f - playerHalfHeight);
		m_PlayerTwoPos.y = Hart::clamp(m_PlayerTwoPos.y, -1.0f + playerHalfHeight, 1.0f - playerHalfHeight);

		if (m_BallPos.x < -1.333f) {
			// player two scores
			m_PlayerTwoScore++;
			reset();
		}
		if (m_BallPos.x > 1.333f) {
			// player one  scores
			m_PlayerOneScore++;
			reset();
		}

		if (m_BallPos.y < -1.0f || m_BallPos.y > 1.0f) {
			m_BallVel.y *= -1.0f;
		}

		if (aabbCollision(m_PlayerOnePos, m_PlayerSize, m_BallPos, m_BallSize)) {
			m_BallVel.x = -m_BallVel.x;
			m_BallPos.x += 0.05f;
		}

		if (aabbCollision(m_PlayerTwoPos, m_PlayerSize, m_BallPos, m_BallSize)) {
			m_BallVel.x = -m_BallVel.x;
			m_BallPos.x -= 0.05f;
		}

		m_BallPos += Hart::Vec3::ScalarMultiply(m_BallVel, BALL_SPEED * deltaTime);
	}

	virtual void render() override {
		Hart::Renderer2D::BeginScene(m_CameraController->getCamera());
		{
			Hart::Renderer2D::DrawQuad(m_PlayerOnePos, m_PlayerSize, Hart::White);
			Hart::Renderer2D::DrawQuad(m_PlayerTwoPos, m_PlayerSize, Hart::White);

			Hart::Renderer2D::DrawLine({ 0.0f, 1.0f }, { 0.0f, -1.0f }, Hart::White);

			Hart::Renderer2D::DrawQuad(m_BallPos, m_BallSize, Hart::White);

			Hart::Renderer2D::DrawText(std::to_string(m_PlayerOneScore), { -0.5f, 0.0f, 0.0f }, 5.0f, Hart::Gray);
			Hart::Renderer2D::DrawText(std::to_string(m_PlayerTwoScore), { 0.3f, 0.0f, 0.0f }, 5.0f, Hart::Gray);
		}
		Hart::Renderer2D::EndScene();
	}

	void reset() {
		m_PlayerOnePos = { -1.2f, 0.0f };
		m_PlayerTwoPos = { 1.2f, 0.0f };
		m_BallPos = { 0.0f, 0.f };
		m_BallVel = { 0.1f, -0.1f };
	}

	bool aabbCollision(const Hart::Vec3& objOnePos, const Hart::Vec3& objOneSize, const Hart::Vec3& objTwoPos, const Hart::Vec3& objTwoSize) {
		return (
			objOnePos.x + objOneSize.x > objTwoPos.x &&
			objOnePos.x < objTwoPos.x + objTwoSize.x &&
			objOnePos.y + objOneSize.y > objTwoPos.y &&
			objOnePos.y < objTwoPos.y + objTwoSize.y);
	}

private:
	Hart::Vec3 m_PlayerOnePos = { -1.2f, 0.0f, 1.0f };
	Hart::Vec3 m_PlayerTwoPos = { 1.2f, 0.0f, 1.0f };
	Hart::Vec2 m_PlayerSize = { 0.08f, 0.4f };

	Hart::Vec3 m_BallPos = { 0.0f, 0.0f, 1.0f };
	Hart::Vec2 m_BallSize = { 0.04f, 0.04f };
	Hart::Vec3 m_BallVel = { 0.1f, -0.1f };

	std::shared_ptr<Hart::Font> m_Font;

	uint32_t m_PlayerOneScore = 0;
	uint32_t m_PlayerTwoScore = 0;
	const float PLAYER_SPEED = 2.0f;
	const float BALL_SPEED = 6.0f;

	std::shared_ptr<Hart::DefaultOrthographicCameraController> m_CameraController;
};

class Game : public Hart::Application {
public:
	Game()
		: Application(640, 480, "Two Player Pong", false) {
		setExitKey(Hart::KeyCode::Escape);

		setBackgroundColor(Hart::Black);

		pushLayer(std::make_shared<GameLayer>());
	}

	~Game() {
	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Game>();
}
