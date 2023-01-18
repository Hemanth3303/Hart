#include "HartPch.hpp"
#include "Event.hpp"

namespace Hart {
	namespace Events {
		Hart::Events::Event::Event(std::string name) 
			: m_Name(name) {

		}

		Event::~Event() {

		}
	}
}