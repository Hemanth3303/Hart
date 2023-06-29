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
	std::shared_ptr<Texture2D> m_Tex1, m_Tex2;
	OrthographicCameraController m_CameraController;
public:
	Layer2D(const std::string& name = "Layer2D")
		:Layer(name), m_CameraController(960.0f, 540.0f, true) {

		m_Tex1 = std::make_shared<Texture2D>("res/images/grass_block.png", TextureMagFilter::Nearest);
		m_Tex2 = std::make_shared<Texture2D>("res/images/awesomeface.png", TextureMagFilter::Linear);
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
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(getCurrentFPS()));
		m_CameraController.update(deltaTime);
	}

	void render() override {
		RenderCommand::SetClearColor(DarkGreenishBlue);

		static float rotationAngle1 = 0;
		static float rotationAngle2 = 0;
		static float rotationAngle3 = 0;
		static float rotationAngle4 = 0;

		Renderer2D::BeginScene(m_CameraController.getCamera());

		Renderer2D::DrawQuad(Vec2(-400, 200), Vec2(50, 50), White);
		Renderer2D::DrawQuad(Vec2(-300, 200), Vec2(50, 50), Black);
		Renderer2D::DrawQuad(Vec2(-200, 200), Vec2(50, 50), Red);
		Renderer2D::DrawQuad(Vec2(-100, 200), Vec2(50, 50), Green);
		Renderer2D::DrawQuad(Vec2(0, 200), Vec2(50, 50), Blue);
		Renderer2D::DrawQuad(Vec2(100, 200), Vec2(50, 50), Yellow);
		Renderer2D::DrawQuad(Vec2(200, 200), Vec2(50, 50), Cyan);
		Renderer2D::DrawQuad(Vec2(300, 200), Vec2(50, 50), Magenta);
		Renderer2D::DrawQuad(Vec2(400, 200), Vec2(50, 50), Gray);
		Renderer2D::DrawQuad(Vec2(-400, 100), Vec2(50, 50), Orange);
		Renderer2D::DrawQuad(Vec2(-300, 100), Vec2(50, 50), Purple);
		Renderer2D::DrawQuad(Vec2(-200, 100), Vec2(50, 50), Pink);
		Renderer2D::DrawQuad(Vec2(-100, 100), Vec2(50, 50), Brown);
		Renderer2D::DrawQuad(Vec2(0, 100), Vec2(50, 50), Teal);
		Renderer2D::DrawQuad(Vec2(100, 100), Vec2(50, 50), Silver);
		Renderer2D::DrawQuad(Vec2(200, 100), Vec2(50, 50), Gold);

		Renderer2D::EndScene();
	}
};