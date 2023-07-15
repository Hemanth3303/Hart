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

// Use discrete GPU by default.
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
extern "C" {
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif

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

		//m_Layer3D = std::make_shared<Layer3D>("TestLayer3D");
		m_Layer2D = std::make_shared<Layer2D>("TestLayer2D");
		//pushLayer(m_Layer3D);
		pushLayer(m_Layer2D);
		
	}

	~Sandbox() {

	}
	
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}