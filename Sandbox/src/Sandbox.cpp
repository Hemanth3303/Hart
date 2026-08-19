/*
 * A Game/App made using Hart-Engine, currently used for testing purposes
 */

//#define HART_REQUEST_DGPU_WINDOWS
#include "Core/EntryPoint.hpp"
#include "Core/Application.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Colors.hpp"
#include "InputCodes/KeyCodes.hpp"
#include "Layer2D.hpp"

#include <memory.h>

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
