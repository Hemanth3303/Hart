#pragma once

#include "Event.hpp"
#include "Core/KeyCodes.hpp"

namespace Hart {
	namespace Events {
		class KeyEvent : public Event {
		public:
			KeyCode getKeyCode() const { return m_KeyCode; }

			virtual int32_t getEventCategoryFlags() const override { return (EventCategory::KeyboardEvent | EventCategory::InputEvent); }

		protected:
			KeyEvent(const KeyCode keyCode)
				: m_KeyCode(keyCode) {

			}
		protected:
			KeyCode m_KeyCode;
		};

		class KeyPressedEvent :public KeyEvent {
		public:
			KeyPressedEvent(const KeyCode keyCode, bool isRepeat = false)
				: KeyEvent(keyCode), m_IsRepeat(isRepeat) {

			}

			bool isRepeat() const { return m_IsRepeat; }

			static EventType GetStaticType() { return EventType::KeyPressed; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "KeyPressed"; }
			std::string toString() const override {
				return "KeyPressed: " + std::to_string(static_cast<int32_t>(m_KeyCode)) + " (repeat = " + std::to_string(m_IsRepeat) + ")";
			}
		private:
			bool m_IsRepeat;
		};

		class KeyReleasedEvent :public KeyEvent {
		public:
			KeyReleasedEvent(const KeyCode keyCode)
				: KeyEvent(keyCode) {

			}

			static EventType GetStaticType() { return EventType::KeyReleased; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "KeyReleased"; }
			std::string toString() const override {
				return "KeyReleased: " + std::to_string(static_cast<int32_t>(m_KeyCode));
			}
		};

		class KeyRepeatEvent : public KeyEvent {
		public:
			KeyRepeatEvent(const KeyCode keyCode)
				: KeyEvent(keyCode) {

			}

			static EventType GetStaticType() { return EventType::KeyRepeat; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "KeyRepeat"; }
			std::string toString() const override {
				return "KeyRepeat: " + std::to_string(static_cast<int32_t>(m_KeyCode));
			}
		};
	}
}