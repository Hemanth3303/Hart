/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Graphics;
using namespace Hart::Maths;
using namespace Hart::Events;
using namespace Hart::Inputs;
using namespace Hart::Utils;

class TileLayer : public Layer {
public:
	TileLayer(Renderer2D* renderer, const Shader& shader, Maths::Mat4 projectionMatrix)
		:Layer(renderer, shader, projectionMatrix) {

	}
	~TileLayer() {

	}
};

class Sandbox : public Application {
private:
	Shader m_BasicShader = Shader("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");

	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);

	std::vector <std::unique_ptr<Renderable2D>> m_Renderables;
	std::unique_ptr<Renderable2D> m_Renderable1, m_Renderable2;
	std::unique_ptr <Renderer2D> m_Renderer;
	std::unique_ptr<TileLayer> m_TileLayer;
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(120);
		setTargetUPS(120);
		setExitKey(KeyCode::Escape);

		m_Renderer = std::make_unique<BatchRenderer2D>();
		m_TileLayer = std::make_unique<TileLayer>(m_Renderer.get(), m_BasicShader, m_Projection);

		m_Renderable1 = std::make_unique<Renderable2D>(100.0f, 100.0f, 50.0f, 50.0f, Vec4(1.0f, 0.0f, 0.0f, 1.0f));
		m_Renderable2 = std::make_unique<Renderable2D>(-100.0f, -100.0f, 100.0f, 25.0f, Vec4(0.0f, 0.0f, 1.0f, 1.0f));
		Random rd;
		for (float y = -270.0f; y <= 270.0f; y+=3.0f) {
			for (float x = -480.0f; x <= 480.0f; x+=3.0f) {
				m_Renderables.emplace_back(std::make_unique<Renderable2D>(
					x, y, 3.0f, 3.0f,
					Vec4(rd.getRandomFloat(0.0f, 1.0f), rd.getRandomFloat(0.0f, 1.0f), rd.getRandomFloat(0.0f, 1.0f), 1.0f)
				));
			}
		}

		m_BasicShader.bind();
		m_BasicShader.setUniform("projection", m_Projection);
		m_BasicShader.unbind();

		m_TileLayer->add(m_Renderable1.get());
		m_TileLayer->add(m_Renderable2.get());
		for (const auto& renderable : m_Renderables) {
			m_TileLayer->add(renderable.get());
		}
	}

	~Sandbox() {

	}

	void update() override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
	}

	void render() override {
		m_TileLayer->render();
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}