#include "HartPch.hpp"
#include "HartApplication.hpp"

namespace Hart {
	namespace Core {

		HartApplication::HartApplication() 
			:m_IsRunning(false) {

		}

		HartApplication::~HartApplication() {

		}

		//protected
		void HartApplication::setConfigs() {

		}

		void HartApplication::tick() {

		}

		//public
		void HartApplication::start() {
			HART_ENGINE_INFO("Starting Engine Systems");

			HART_ENGINE_INFO("Applying Configurations");
			setConfigs();

			HART_ENGINE_INFO("Calling your implementation of init()");
			init();
		}

		void HartApplication::run() {
			HART_ENGINE_INFO("Starting Engine Loop");
			while (m_IsRunning) {
				tick();
				update();
				render();
			}
		}

		void HartApplication::shutdown() {
			HART_ENGINE_INFO("Calling your implementation of deinit()");
			deinit();
			HART_ENGINE_INFO("Shutting Down Engine Systems");
		}

	}
}