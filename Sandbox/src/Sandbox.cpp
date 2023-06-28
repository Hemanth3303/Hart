/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"
#include "Layer3D.hpp"

using namespace Hart;
using namespace Hart::Graphics;
using namespace Hart::Maths;
using namespace Hart::Events;
using namespace Hart::Inputs;
using namespace Hart::Utils;

class Sandbox : public Application {
private:
	std::shared_ptr<Layer3D> m_Layer3D;
public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) {
		setMaxFPS(144);
		//enableVsync();
		setExitKey(KeyCode::Escape);

		m_Layer3D = std::make_shared<Layer3D>("Test Layer3D");
		pushLayer(m_Layer3D);
	}

	~Sandbox() {

	}
	
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}