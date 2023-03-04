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

	std::vector <std::unique_ptr<DynamicRenderable2D>> renderables;
	std::unique_ptr<DynamicRenderable2D> renderable1, renderable2;
	BatchRenderer2D renderer;
public:
	Sandbox() 
		: Application(960, 540, "Hart Engine: Sandbox", true) {

		setTargetFPS(120);
		setTargetUPS(120);
		setExitKey(KeyCode::Escape);

		basicShader = std::make_shared<Shader>("res/shaders/basicVert.glsl", "res/shaders/basicFrag.glsl");
		

		renderable1 = std::make_unique<DynamicRenderable2D>(
			Vec3(100.0f, 100.0f, 0.0f),
			Vec2(50.0f, 50.0f),
			Vec4(1.0f, 0.0f, 0.0f, 1.0f)
		);
		renderable2 = std::make_unique<DynamicRenderable2D>(
			Vec3(-100.0f, -100.0f, 0.0f),
			Vec2(100.0f, 25.0f),
			Vec4(0.0f, 0.0f, 1.0f, 1.0f)
		);
		Random rd;
		for (float y = -270.0f; y <= 270.0f; y+=5.4f) {
			for (float x = -480.0f; x <= 480.0f; x+=9.6f) {
				renderables.emplace_back(std::make_unique<DynamicRenderable2D>(
					Vec3(x, y, 0.0f),
					Vec2(9.6f, 5.4f),
					Vec4(rd.getRandomFloat(0.0f, 1.0f), rd.getRandomFloat(0.0f, 1.0f), rd.getRandomFloat(0.0f, 1.0f), 1.0f)
				));
			}
		}

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
		basicShader->bind();
		renderer.begin();
		
		renderer.submit(renderable1.get());
		renderer.submit(renderable2.get());

		for (const auto& renderable : renderables) {
			renderer.submit(renderable.get());
		}

		renderer.flush();

		renderer.end();
		basicShader->unbind();
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}