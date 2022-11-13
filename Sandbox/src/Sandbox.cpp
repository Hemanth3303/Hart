/*
* A Game/App made using Hart-Engine, currently used for testing purposes
*/

#include "Hart.hpp"

class Sandbox : public Hart::Application {
public:
	Sandbox() {
		using namespace Hart;
		using namespace Hart::Utils;

		HART_ENGINE_TRACE("HTrace");
		HART_ENGINE_INFO("HInfo");
		HART_ENGINE_WARNING("HWarning");
		HART_ENGINE_ERROR("HError");
		HART_ENGINE_FATAL("HFatal");

		std::cout << "\n\n";

		HART_CLIENT_TRACE("CTrace");
		HART_CLIENT_INFO("CInfo");
		HART_CLIENT_WARNING("CWarning");
		HART_CLIENT_ERROR("CError");
		HART_CLIENT_FATAL("CFatal");

		std::cout << "\nNon logger message\n";
	}

	~Sandbox() {

	}

	void update() override {
		
	}

	void render() override {

	}
};

Hart::Application* Hart::CreateApplication() {
	return new Sandbox();
}