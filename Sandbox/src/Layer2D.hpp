#pragma once

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Graphics;
using namespace Hart::Maths;
using namespace Hart::Events;
using namespace Hart::Inputs;
using namespace Hart::Utils;

class Layer2D : public Layer {
private:
	std::shared_ptr<Texture2D> m_GrassTex, m_EmojiTex, m_SpriteSheet;
	OrthographicCameraController m_CameraController;
	Random m_Rd;
	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;
public:
	Layer2D(const std::string& name = "Layer2D")
		:Layer(name), m_CameraController(960.0f, 540.0f), m_ParticleSystem(1'000'000) {

		m_GrassTex = std::make_shared<Texture2D>("res/images/grass_block.png", TextureMagFilter::Nearest);
		m_EmojiTex = std::make_shared<Texture2D>("res/images/awesomeface.png", TextureMagFilter::Linear);
		m_SpriteSheet = std::make_shared<Texture2D>("res/images/RPGpack_sheet_2X.png", TextureMagFilter::Nearest);

		m_Particle.colorBegin = FireRed;
		m_Particle.colorEnd = White;
		m_Particle.sizeBegin = 30.0f, m_Particle.sizeVariation = 0.3f, m_Particle.sizeEnd = 0.0f;
		m_Particle.lifeTime = 2.0f;
		m_Particle.velocity = { m_Rd.getRandomFloat(-10, 10), m_Rd.getRandomFloat(-10, 10) };
		m_Particle.velocityVariation = { m_Rd.getRandomFloat(-20, 20),  m_Rd.getRandomFloat(-20, 20) };
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

	void onEvent(Event& e) override {
		//HART_CLIENT_LOG(e);
		m_CameraController.onEvent(e);
	}

	void update(const float deltaTime) override {
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(1.0f / deltaTime));
		
		auto [x, y] = InputManager::GetMousePosition();
		std::int32_t width = Application::Get()->getWindowWidth();
		std::int32_t height = Application::Get()->getWindowHeight();

		OrthographicCameraBounds bounds = m_CameraController.getBounds();
		Maths::Vec3 position = m_CameraController.getCamera().getPosition();
		x = (x / width) * bounds.getWidth() - bounds.getWidth() * 0.5f;
		y = bounds.getHeight() * 0.5f - (y / height) * bounds.getHeight();
		m_Particle.position = { x + position.x, y + position.y , 1.0f };
		
		if (InputManager::IsMouseButtonPressed(MouseCode::Left)) {
			m_ParticleSystem.emit(m_Particle);
		}

		m_CameraController.update(deltaTime);
		m_ParticleSystem.update(deltaTime);
	}

	void render() override {
		Renderer2D::ResetStats();
		Renderer2D::BeginScene(m_CameraController.getCamera());

		//for (float y = -270; y <= 270; y += 30) {
		//	for (float x = -480; x <= 480; x += 30) {
		//		Renderer2D::DrawQuad(Vec3(x, y, -0.1f), Vec2(30, 30), m_GrassTex);
		//	}
		//}

		//Renderer2D::DrawQuad(Vec3(100, 100), Vec2(50, 150), Red);
		//Renderer2D::DrawQuad(Vec3(-100, -100), Vec2(150, 50), Blue);

		//Renderer2D::DrawQuad(Vec3(130, -50), Vec2(100, 100), m_GrassTex);
		//Renderer2D::DrawQuad(Vec3(-280, -100), Vec2(100, 100), m_EmojiTex);

		Renderer2D::DrawQuad({ 0, 0 }, { 300, 300 }, m_SpriteSheet);

		m_ParticleSystem.render();

		Renderer2D::EndScene();
		//HART_CLIENT_TRACE("No of drawcalls: " + std::to_string(Renderer2D::GetNumberOfDrawCalls()));
		//HART_CLIENT_TRACE("No of quads: " + std::to_string(Renderer2D::GetNumberOfQuads()));
		//HART_CLIENT_TRACE("No of vertices: " + std::to_string(Renderer2D::GetNumberOfVertices()));
		//HART_CLIENT_TRACE("No of indices: " + std::to_string(Renderer2D::GetNumberOfIndices()));
	}
};