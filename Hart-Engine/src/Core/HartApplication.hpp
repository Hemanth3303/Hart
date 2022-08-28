/*
* Not sure I'm happy with this approach? Too Object Oriented?
* TODO: Re-Evaluate this and make changes if required
*/


#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Core {
		class HartApplication {
		protected:
			HartApplication();
			HartApplication(const HartApplication&) = delete;
			virtual ~HartApplication();

			//TODO:
			//add methods for adding and removing scenes, layers, etc, when engine has those functions

			/*To be implemented by client if not happy with the defaults*/

			//window and game configurations, implement if needed
			virtual void setConfigs();
			//runs once per second, implement if needed
			virtual void tick();

			/*Must be implemented by client to run game*/

			virtual void init() = 0;
			virtual void update() = 0;
			virtual void render() = 0;
			virtual void deinit() = 0;
		public:
			//starts the engine and calls clients implementation of setConfigs(optional) and init
			void start();
			//runs tick(optional), update, and render in a **WHILE LOOP,**
			//do NOT put this function in a while loop
			void run();
			//calls clients implementation of deinit and shuts down the engine
			void shutdown();

			inline const bool& isRunnig() const { return m_IsRunning; }
		private:
			bool m_IsRunning;
		};
	}
}