/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"
#include "Layer2D.hpp"
#include "Layer3D.hpp"

class Sandbox : public Hart::Application {
private:
	std::shared_ptr<Layer2D> m_Layer2D;
	std::shared_ptr<Layer3D> m_Layer3D;
public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) {
		setMaxFPS(144);
		//enableVsync();
		setExitKey(Hart::KeyCode::Escape);
		setBackgroundColor(Hart::DarkGreenishBlue);

		m_Layer2D = std::make_shared<Layer2D>("Layer2D");
		m_Layer3D = std::make_shared<Layer3D>("Layer3D");

		pushLayer(m_Layer2D);
		pushLayer(m_Layer3D);
	}

	~Sandbox() {

	}
	
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}