#pragma once

#include "Hart.hpp"

class Layer2D : public Hart::Layer {
private:
	std::shared_ptr<Hart::Texture2D> m_GrassTex, m_EmojiTex;
	std::shared_ptr<Hart::SpriteSheet> m_SpriteSheet;
	std::shared_ptr<Hart::OrthographicCameraController> m_CameraController;
	Hart::Random m_Rd;
	Hart::ParticleProps m_Particle;
	Hart::ParticleSystem m_ParticleSystem;
	Hart::Vec3 m_MousePos = { 0.0f, 0.0f, 1.0f };
public:
	Layer2D(const std::string& name = "Layer2D")
		: Layer(name), m_ParticleSystem(1'000'000) {
	}

	~Layer2D() {

	}

	void onAttach() override {
		HART_CLIENT_LOG(std::string("Attached layer: ") + getName());

		Hart::Texture2DSpecification pixelArtTextureSpec;
		pixelArtTextureSpec.magFilter = Hart::TextureMagFilter::Nearest;

		m_GrassTex = std::make_shared<Hart::Texture2D>("res/images/grass_block.png", pixelArtTextureSpec);
		m_EmojiTex = std::make_shared<Hart::Texture2D>("res/images/awesomeface.png");
		m_SpriteSheet = std::make_shared<Hart::SpriteSheet>("res/images/RPGpack_sheet_2X.png", Hart::Vec2(128, 128), pixelArtTextureSpec);

		m_CameraController = std::make_shared<Hart::DefaultOrthographicCameraController>(960.0f, 540.0f);

		m_Particle.colorBegin = Hart::FireRed;
		m_Particle.colorEnd = Hart::White;
		m_Particle.sizeBegin = 0.08f, m_Particle.sizeVariation = 0.001f, m_Particle.sizeEnd = 0.0f;
		m_Particle.lifeTime = 2.0f;
		m_Particle.velocity = { m_Rd.getRandomFloat(-1.0f, 1.0f), m_Rd.getRandomFloat(-1.0f, 1.0f) };
		m_Particle.velocityVariation = { m_Rd.getRandomFloat(-2.0f, 2.0f),  m_Rd.getRandomFloat(-2.0f, 2.0f) };
		m_Particle.position = { 0.0f, 0.0f, 1.0f };

	}

	void onDetach() override {
		HART_CLIENT_LOG(std::string("Detached layer: ") + getName());
	}

	void onEvent(Hart::Event& e) override {
		//HART_CLIENT_LOG(e);
		m_CameraController->onEvent(e);
	}

	void update(const float deltaTime) override {
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(Hart::Application::Get()->getCurrentFPS()));

		auto [x, y] = Hart::InputManager::GetMousePosition();
		std::int32_t width = Hart::Application::Get()->getWindowWidth();
		std::int32_t height = Hart::Application::Get()->getWindowHeight();

		Hart::OrthographicCameraBounds bounds = m_CameraController->getBounds();
		Hart::Vec3 position = m_CameraController->getCamera().getPosition();
		x = (x / width) * bounds.getWidth() - bounds.getWidth() * 0.5f;
		y = bounds.getHeight() * 0.5f - (y / height) * bounds.getHeight();
		m_Particle.position = { x + position.x, y + position.y , 1.0f };

		m_MousePos.x = x;
		m_MousePos.y = y;

		if (Hart::InputManager::IsMouseButtonPressed(Hart::MouseCode::Left)) {
			m_ParticleSystem.emit(m_Particle);
		}

		m_CameraController->update(deltaTime);
		m_ParticleSystem.update(deltaTime);
	}

	void render() override {
		Hart::Renderer2D::ResetStats();
		Hart::Renderer2D::BeginScene(m_CameraController->getCamera());

		//Hart::Renderer2D::DrawLine({ -0.5f, -0.5f }, { 0.5f, -0.5f }, Hart::Red);
		//Hart::Renderer2D::DrawLine({ 0.5f, -0.5f }, { 0.0f,  0.5f }, Hart::Blue);
		//Hart::Renderer2D::DrawLine({ 0.0f,  0.5f }, { -0.5f, -0.5f }, Hart::Green);

		//Hart::Renderer2D::DrawLine({ 0.0f, 0.0f, 1.0f }, m_MousePos, Hart::Cyan);

		//Hart::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, m_GrassTex);
		//Hart::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 0.5f, 0.5f }, m_EmojiTex);
		//Hart::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.5f, 0.5f }, m_SpriteSheet, { 0, 0 });

		//m_ParticleSystem.render();

		Hart::Renderer2D::DrawText("Hello, World!", { 0.0f, 0.0f, 1.0f }, 0.5f, Hart::Red);
		Hart::Renderer2D::DrawText("Hart Engine!!!!!", { 0.5f, 0.5f, 1.0f }, 0.5f, Hart::Blue);

		Hart::Renderer2D::EndScene();
		//HART_CLIENT_TRACE("No of drawcalls: " + std::to_string(Hart::Renderer2D::GetNumberOfDrawCalls()));
		//HART_CLIENT_TRACE("No of quads: " + std::to_string(Hart::Renderer2D::GetNumberOfQuads()));
		//HART_CLIENT_TRACE("No of quad vertices: " + std::to_string(Hart::Renderer2D::GetNumberOfQuadVertices()));
		//HART_CLIENT_TRACE("No of quad indices: " + std::to_string(Hart::Renderer2D::GetNumberOfQuadIndices()));
		//HART_CLIENT_TRACE("No of lines: " + std::to_string(Hart::Renderer2D::GetNumberOfLines()));
		//HART_CLIENT_TRACE("No of line vertices: " + std::to_string(Hart::Renderer2D::GetNumberOfLineVertices()));
	}
};