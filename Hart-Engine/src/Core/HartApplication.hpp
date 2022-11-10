#pragma once

namespace Hart {
	class Application {
	public:
		Application();
		virtual ~Application();

		void run();
	protected:
		virtual void update() = 0;
		virtual void render() = 0;
	};

	Application* CreateApplication();
}