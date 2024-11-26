// Example Game: Two player controlled pong game

#include "Core/EntryPoint.hpp"
#include "Hart.hpp"

class GameLayer :public Hart::Layer {
public:
	GameLayer(const std::string& name = "GameLayer") 
		:Layer(name) {

	}
	~GameLayer() {

	}

	virtual void onAttach() override {
		m_CameraController = std::make_shared<Hart::DefaultOrthographicCameraController>(640.0f, 480.0f, false);
		// disabling camera movement
		m_CameraController->setMovementSpeed(0.0f);
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

		float halfHeight = m_PlayerSize.y / 2.0f;
		m_PlayerOnePos.y = Hart::clamp(m_PlayerOnePos.y, -1.0f + halfHeight, 1.0f - halfHeight);
		m_PlayerTwoPos.y = Hart::clamp(m_PlayerTwoPos.y, -1.0f + halfHeight, 1.0f - halfHeight);
	}

	virtual void render() override {
		Hart::Renderer2D::BeginScene(m_CameraController->getCamera());
		{
			Hart::Renderer2D::DrawQuad(m_PlayerOnePos, m_PlayerSize, Hart::White);
			Hart::Renderer2D::DrawQuad(m_PlayerTwoPos, m_PlayerSize, Hart::White);
			
			Hart::Renderer2D::DrawLine({ 0.0f, 1.0f }, { 0.0f, -1.0f }, Hart::White);

			Hart::Renderer2D::DrawQuad(m_BallPos, m_BallSize, Hart::White);

		}
		Hart::Renderer2D::EndScene();
	}
private:
	Hart::Vec3 m_PlayerOnePos={ -1.2f, 0.0f };
	Hart::Vec3 m_PlayerTwoPos = { 1.2f, 0.0f };
	Hart::Vec2 m_PlayerSize = { 0.08f, 0.4f };

	Hart::Vec3 m_BallPos = { 0.0f, 0.f };
	Hart::Vec2 m_BallSize = { 0.04f, 0.04f };

	std::uint32_t m_PlayerScore = 0;
	const float PLAYER_SPEED = 2.0f;
	const float BALL_SPEED = 5.0f;

	std::shared_ptr<Hart::DefaultOrthographicCameraController> m_CameraController;
};

class Game : public Hart::Application {
public:
	Game()
		: Application(640, 480, "Two Player Pong", false) {
		setMaxFPS(60.0);
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