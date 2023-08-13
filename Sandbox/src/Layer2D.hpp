#pragma once

#include "Hart.hpp"

class Layer2D : public Hart::Layer {
private:
	std::shared_ptr<Hart::Graphics::Texture2D> m_GrassTex, m_EmojiTex;
	std::shared_ptr<Hart::Graphics::SpriteSheet> m_SpriteSheet;
	std::shared_ptr<Hart::Graphics::OrthographicCameraController> m_CameraController;
	Hart::Utils::Random m_Rd;
	Hart::Graphics::ParticleProps m_Particle;
	Hart::Graphics::ParticleSystem m_ParticleSystem;
public:
	Layer2D(const std::string& name = "Layer2D")
		:Layer(name), m_ParticleSystem(1'000'000) {

		m_GrassTex = std::make_shared<Hart::Graphics::Texture2D>("res/images/grass_block.png", Hart::Graphics::TextureMagFilter::Nearest);
		m_EmojiTex = std::make_shared<Hart::Graphics::Texture2D>("res/images/awesomeface.png", Hart::Graphics::TextureMagFilter::Linear);
		m_SpriteSheet = std::make_shared<Hart::Graphics::SpriteSheet>("res/images/RPGpack_sheet_2X.png", Hart::Maths::Vec2(128, 128), Hart::Graphics::TextureMagFilter::Nearest);

		m_CameraController = std::make_shared<Hart::Graphics::DefaultOrthographicCameraController>(960.0f, 540.0f);

		m_Particle.colorBegin = Hart::Graphics::FireRed;
		m_Particle.colorEnd = Hart::Graphics::White;
		m_Particle.sizeBegin = 0.08f, m_Particle.sizeVariation = 0.001f, m_Particle.sizeEnd = 0.0f;
		m_Particle.lifeTime = 2.0f;
		m_Particle.velocity = { m_Rd.getRandomFloat(-1.0f, 1.0f), m_Rd.getRandomFloat(-1.0f, 1.0f) };
		m_Particle.velocityVariation = { m_Rd.getRandomFloat(-2.0f, 2.0f),  m_Rd.getRandomFloat(-2.0f, 2.0f) };
		m_Particle.position = { 0.0f, 0.0f, 1.0f };
	}

	~Layer2D() {

	}

	void onAttach() override {
		HART_CLIENT_LOG(std::string("Attached layer: ") + getName());
	}
	
	void onDetach() override {
		HART_CLIENT_LOG(std::string("Detached layer: ") + getName());
	}

	void onEvent(Hart::Events::Event & e) override {
		//HART_CLIENT_LOG(e);
		m_CameraController->onEvent(e);
	}

	void update(const float deltaTime) override {
		HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(Hart::Application::Get()->getCurrentFPS()));
		
		auto [x, y] = Hart::Inputs::InputManager::GetMousePosition();
		std::int32_t width = Hart::Application::Get()->getWindowWidth();
		std::int32_t height = Hart::Application::Get()->getWindowHeight();

		Hart::Graphics::OrthographicCameraBounds bounds = m_CameraController->getBounds();
		Hart::Maths::Vec3 position = m_CameraController->getCamera().getPosition();
		x = (x / width) * bounds.getWidth() - bounds.getWidth() * 0.5f;
		y = bounds.getHeight() * 0.5f - (y / height) * bounds.getHeight();
		m_Particle.position = { x + position.x, y + position.y , 1.0f };
		
		if (Hart::Inputs::InputManager::IsMouseButtonPressed(Hart::Inputs::MouseCode::Left)) {
			m_ParticleSystem.emit(m_Particle);
		}

		m_CameraController->update(deltaTime);
		m_ParticleSystem.update(deltaTime);
	}

	void render() override {
		using namespace Hart::Maths;
		using namespace Hart::Graphics;

		Renderer2D::ResetStats();
		Renderer2D::BeginScene(m_CameraController->getCamera());

		Renderer2D::DrawLine({ 0, 0 }, { 0.5, 0 }, Red);
		Renderer2D::DrawLine({ 0.5, 0 }, { 0.5, 0.5 }, Blue);

		Renderer2D::DrawLine({ -0.5, 0 }, { 0.5, -0.5 }, Magenta);
		
		m_ParticleSystem.render();

		Hart::Graphics::Renderer2D::EndScene();
		HART_CLIENT_TRACE("No of drawcalls: " + std::to_string(Hart::Graphics::Renderer2D::GetNumberOfDrawCalls()));
		HART_CLIENT_TRACE("No of quads: " + std::to_string(Hart::Graphics::Renderer2D::GetNumberOfQuads()));
		HART_CLIENT_TRACE("No of quad vertices: " + std::to_string(Hart::Graphics::Renderer2D::GetNumberOfQuadVertices()));
		HART_CLIENT_TRACE("No of quad indices: " + std::to_string(Hart::Graphics::Renderer2D::GetNumberOfQuadIndices()));
		HART_CLIENT_TRACE("No of lines: " + std::to_string(Hart::Graphics::Renderer2D::GetNumberOfLines()));
		HART_CLIENT_TRACE("No of line vertices: " + std::to_string(Hart::Graphics::Renderer2D::GetNumberOfLineVertices()));
	}
};