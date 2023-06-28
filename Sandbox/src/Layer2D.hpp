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
	ShaderLibrary m_ShaderLibrary;
	OrthographicCameraController m_CameraController;
public:
	Layer2D(const std::string& name = "Layer2D")
		:Layer(name), m_CameraController(960.0f / 540.0f) {

		m_CameraController.setRotationSpeed(45);

		m_ShaderLibrary.loadShader("textureShader", "res/shaders/textureVert.glsl", "res/shaders/textureFrag.glsl");
		m_Tex1 = std::make_shared<Texture2D>("res/images/grass_block.png", TextureMagFilter::Nearest);
		m_Tex2 = std::make_shared<Texture2D>("res/images/awesomeface.png", TextureMagFilter::Linear);

		m_CameraController.setMovementSpeed(7);

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
		RenderCommand::SetClearColor({ 18.0f, 18.0f, 18.0f, 255.0f });

		Renderer2D::BeginScene(m_CameraController.getCamera(), m_ShaderLibrary.getShader("textureShader"));
		Renderer2D::DrawQuad(Vec2(0.0f, 0.0f), Vec2(0.4f, 0.4f), 0.0f, Vec4(255.0f, 0.0f, 0.0f, 255.0f));
		Renderer2D::DrawQuad(Vec3(0.0f, 0.0f, 1.0f), Vec2(1.0f, 1.0f), 45, m_Tex2);
		Renderer2D::EndScene();
	}
};