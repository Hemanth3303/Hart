﻿/*
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
		setMaxFPS(144);
		//enableVsync();
		setExitKey(Hart::KeyCode::Escape);
		setBackgroundColor(Hart::DarkGreenishBlue);

		m_Layer2D = std::make_shared<Layer2D>("Layer2D");

		pushLayer(m_Layer2D);
	}

	~Sandbox() {
		HART_CLIENT_LOG("Deinitialising Sandbox");
	}
	
};

std::unique_ptr<Hart::Application> Hart::CreateApplication() {
	return std::make_unique<Sandbox>();
}