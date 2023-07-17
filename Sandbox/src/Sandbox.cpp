/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"
#include "Layer3D.hpp"
#include "Layer2D.hpp"

using namespace Hart;
using namespace Hart::Graphics;
using namespace Hart::Maths;
using namespace Hart::Events;
using namespace Hart::Inputs;
using namespace Hart::Utils;

class TestLayer : public Layer {
private:
	std::shared_ptr<Texture2D> m_GrassTex, m_EmojiTex;
	OrthographicCameraController m_CameraController;
	Random m_Rd;
public:
	TestLayer(const std::string& name = "TestLayer")
		:Layer(name), m_CameraController(960.0f, 540.0f) {

		m_GrassTex = std::make_shared<Texture2D>("res/images/grass_block.png", TextureMagFilter::Nearest);
		m_EmojiTex = std::make_shared<Texture2D>("res/images/awesomeface.png", TextureMagFilter::Linear);
	}

	~TestLayer() {

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
		Renderer2D::BeginScene(m_CameraController.getCamera());
		
		Renderer2D::DrawQuad({ 0, 0, 1 }, { 300, 300 }, Gray);

		//HART_CLIENT_TRACE("No of quads: " + std::to_string(count));
		//HART_CLIENT_TRACE("No of drawcalls: " + std::to_string(Renderer2D::GetNumberOfDrawCalls()));
		Renderer2D::EndScene();
	}
};

class Sandbox : public Application {
private:
	std::shared_ptr<Layer3D> m_Layer3D;
	std::shared_ptr<Layer2D> m_Layer2D;
public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) {
		setMaxFPS(144);
		//enableVsync();
		setExitKey(KeyCode::Escape);

		RenderCommand::SetClearColor(DarkGreenishBlue);

		//m_Layer3D = std::make_shared<Layer3D>("Layer3D");
		m_Layer2D = std::make_shared<Layer2D>("Layer2D");
		//pushLayer(m_Layer3D);
		pushLayer(m_Layer2D);
		pushOverlay(std::make_shared<TestLayer>("TestLayer"));
	}

	~Sandbox() {

	}
	
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}