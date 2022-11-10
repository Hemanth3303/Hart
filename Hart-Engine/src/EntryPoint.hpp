#pragma once

#include "Core/HartApplication.hpp"

extern Hart::Application* Hart::CreateApplication();

int main(int argc, char** argv) {
	Hart::Application* app = Hart::CreateApplication();
	app->run();
	delete app;
}
