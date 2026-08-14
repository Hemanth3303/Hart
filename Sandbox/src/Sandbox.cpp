/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Core/EntryPoint.hpp"
#include "Hart.hpp"
#include "Layer2D.hpp"

class Sandbox : public Hart::Application {
private:
	std::shared_ptr<Layer2D> m_Layer2D;
public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) {
		HART_CLIENT_LOG("Initialising Sandbox");
		setMaxFPS(1000);
		enableVsync(false);
		setExitKey(Hart::KeyCode::Escape);
		setBackgroundColor(Hart::DarkGreenishBlue);

		m_Layer2D = std::make_shared<Layer2D>("Layer2D");

		std::cout << Hart::Vec3::CrossProduct(Hart::Vec3(1, 0, 0), Hart::Vec3(0, 1, 0)) << '\n';
		std::cout << Hart::Vec3::CrossProduct(Hart::Vec3(0, 1, 0), Hart::Vec3(1, 0, 0)) << '\n';

		pushLayer(m_Layer2D);
	}

	~Sandbox() {
		HART_CLIENT_LOG("DeInitialising Sandbox");
	}

};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}
