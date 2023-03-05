/*
* Keypressed, keyreleased and keyrepeat
*/

#pragma once

#include "Event.hpp"
#include "Inputs/KeyCodes.hpp"

namespace Hart {
	namespace Events {
		class KeyEvent : public Event {
		public:
			Inputs::KeyCode getKeyCode() const { return m_KeyCode; }

			virtual int32_t getEventCategoryFlags() const override { return (EventCategory::KeyboardEvent | EventCategory::InputEvent); }

		protected:
			KeyEvent(const Inputs::KeyCode keyCode)
				: m_KeyCode(keyCode) {

			}
		protected:
			Inputs::KeyCode m_KeyCode;
		};

		class KeyPressedEvent :public KeyEvent {
		public:
			KeyPressedEvent(const Inputs::KeyCode keyCode)
				: KeyEvent(keyCode) {

			}

			static EventType GetStaticType() { return EventType::KeyPressedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "KeyPressedEvent"; }
			std::string toString() const override {
				return "KeyPressedEvent: " + std::to_string(static_cast<int32_t>(m_KeyCode));
			}
		};

		class KeyReleasedEvent :public KeyEvent {
		public:
			KeyReleasedEvent(const Inputs::KeyCode keyCode)
				: KeyEvent(keyCode) {

			}

			static EventType GetStaticType() { return EventType::KeyReleasedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "KeyReleasedEvent"; }
			std::string toString() const override {
				return "KeyReleasedEvent: " + std::to_string(static_cast<int32_t>(m_KeyCode));
			}
		};

		class KeyRepeatEvent : public KeyEvent {
		public:
			KeyRepeatEvent(const Inputs::KeyCode keyCode, int32_t repeatCount)
				: KeyEvent(keyCode), m_RepeatCount(repeatCount) {

			}

			const int32_t& getRepeatCount() const { return m_RepeatCount; }

			static EventType GetStaticType() { return EventType::KeyRepeatEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "KeyRepeatEvent"; }
			std::string toString() const override {
				return "KeyRepeat: " + std::to_string(static_cast<int32_t>(m_KeyCode)) + " (repeat count = "+std::to_string(m_RepeatCount) + ")";
			}
		private:
			int32_t m_RepeatCount;
		};
	}
}