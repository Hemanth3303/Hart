/*
* Event Interface
*/

#pragma once

#include "HartPch.hpp"

namespace Hart {
	namespace Events {
		class Event {
		protected:
			std::string m_Name;
		public:
			Event(std::string name);
			virtual ~Event();

			inline const std::string& getName() { return m_Name; }
		};
	}
}