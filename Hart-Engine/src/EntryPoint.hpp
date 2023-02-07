/*
* Entry point of any Hart Application
*/

#pragma once

#ifdef _MSC_VER
#pragma warning(disable: 5105) 
#endif // _MSC_VER

#include "Core/HartApplication.hpp"

extern std::unique_ptr<Hart::Application> Hart::CreateApplication();

int main(int argc, char** argv) {
	std::unique_ptr<Hart::Application> app = Hart::CreateApplication();

	app->run();

	return 0;
}
