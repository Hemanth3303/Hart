/*
 * A Game/App made using Hart-Engine, currently used for testing purposes
 */

#if defined(HART_CLIENT_RELEASE_BUILD)
	#define HART_REQUEST_DGPU_WINDOWS
#endif
#include "Core/EntryPoint.hpp"
#include "Hart.hpp"
#include "Layer2D.hpp"

class Sandbox : public Hart::Application {
private:
	std::shared_ptr<Layer2D> m_Layer2D;

public:
	Sandbox()
		: Application(960, 540, "Hart Engine: Sandbox", true) {
		HART_CLIENT_INFO("Initialising SandboxApp");
		enableVsync(false);
		setExitKey(Hart::KeyCode::Escape);
		setBackgroundColor(Hart::DarkGreenishBlue);

		m_Layer2D = std::make_shared<Layer2D>("SandboxLayer2D");
		pushLayer(m_Layer2D);
	}

	~Sandbox() {
		HART_CLIENT_INFO("DeInitialising Sandbox");
	}
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}
