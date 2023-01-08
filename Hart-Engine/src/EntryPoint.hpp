/*
* Entry point of any Hart Application
*/

#pragma once

#ifdef _MSC_VER
#pragma warning(disable: 5105) 
#endif // _MSC_VER

#include "Core/HartApplication.hpp"

extern Hart::Application* Hart::CreateApplication();

int main(int argc, char** argv) {
	Hart::Application* app = Hart::CreateApplication();
	app->run();
	delete app;

	return 0;
}
