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
	Random m_Rd;
public:
	Layer2D(const std::string& name = "Layer2D")
		:Layer(name), m_CameraController(960.0f, 540.0f) {

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
		int count = 0;
		Renderer2D::BeginScene(m_CameraController.getCamera());
		//for (float y = -270; y <= 270; y += 50) {
		//	for (float x = -480; x <= 480; x += 50) {
		//		Renderer2D::DrawQuad(Vec3(x, y, -0.1f), Vec2(50, 50), m_Tex1);
		//		count++;
		//	}
		//}
		
		Renderer2D::DrawQuad(Vec3(100, 100), Vec2(50, 150), Red);
		Renderer2D::DrawQuad(Vec3(-100, -100), Vec2(150, 50), Blue);

		Renderer2D::DrawQuad(Vec3(130, -50), Vec2(100, 100), m_Tex1, White, 5);
		Renderer2D::DrawQuad(Vec3(-280, -100), Vec2(100, 100), m_Tex2, Red);

		//HART_CLIENT_TRACE("No of quads: " + std::to_string(count));
		//HART_CLIENT_TRACE("No of drawcalls: " + std::to_string(Renderer2D::GetNumberOfDrawCalls()));
		Renderer2D::EndScene();
	}
};