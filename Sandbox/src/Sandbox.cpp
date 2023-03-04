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

class Sandbox : public Application {
private:
	std::shared_ptr<Shader> basicShader;

	//to make (0,0) at center of game window
	Mat4 m_Projection = Mat4::orthographic(-(960/2.0f), (960/2.0f), -(540/2.0f), (540/2.0f), -1.0f, 1.0f);

	std::unique_ptr<Renderable2D> renderable1, renderable2;
	SimpleRenderer2D renderer;
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(120);
		setTargetUPS(120);
		setExitKey(KeyCode::Escape);

		basicShader = std::make_shared<Shader>("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");
		

		renderable1 = std::make_unique<Renderable2D>(
			Vec3(100.0f, 100.0f, 0.0f), 
			Vec2(50.0f, 50.0f), 
			Vec4(1.0f, 0.0f, 0.0f, 1.0f), 
			basicShader
		
		);
		renderable2 = std::make_unique<Renderable2D>(
			Vec3(-100.0f, -100.0f, 0.0f),
			Vec2(100.0f, 25.0f),
			Vec4(0.0f, 0.0f, 1.0f, 1.0f),
			basicShader
		);

		basicShader->bind();
		basicShader->setUniform("projection", m_Projection);
		basicShader->unbind();

	}

	~Sandbox() {

	}

	void update() override {
		//HART_CLIENT_LOG("FPS: " + std::to_string(getCurrentFPS()) + " | UPS: " + std::to_string(getCurrentUPS()));
		
	}

	void render() override {
		renderer.begin();
		
		renderer.submit(renderable1.get());
		renderer.submit(renderable2.get());
		renderer.flush();

		renderer.end();
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}