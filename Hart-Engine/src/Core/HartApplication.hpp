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
	private:
		void init();
		void deinit();
		void handleEvents();
	private:
		bool m_IsRunning = false;
	};

	Application* CreateApplication();
}