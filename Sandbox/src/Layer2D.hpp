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
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(1.0f / deltaTime));
		m_CameraController.update(deltaTime);
	}

	void render() override {
		Random rd;

		Renderer2D::BeginScene(m_CameraController.getCamera());
		Renderer2D::DrawQuad({ 100, -20, 0}, { 100, 200 }, Magenta);
		Renderer2D::EndScene();
	}
};