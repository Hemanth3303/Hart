/*
* Keypressed, keyreleased and keyrepeat
*/

#pragma once

#include "Event.hpp"
#include "Inputs/KeyCodes.hpp"

namespace Hart {
	// Base class for key events
	class KeyEvent : public Event {
	public:
		KeyCode getKeyCode() const { return m_KeyCode; }

		virtual std::int32_t getEventCategoryFlags() const override { return (EventCategory::KeyboardEvent | EventCategory::InputEvent); }

	protected:
		KeyEvent(const KeyCode keyCode)
			: m_KeyCode(keyCode) {

		}
	protected:
		KeyCode m_KeyCode;
	};

	class KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode keyCode)
			: KeyEvent(keyCode) {

		}

		static EventType GetStaticType() { return EventType::KeyPressedEvent; }
		virtual EventType getEventType() const override { return GetStaticType(); }
		virtual std::string_view getName() const override { return "KeyPressedEvent"; }
		std::string toString() const override {
			return "KeyPressedEvent: " + std::to_string(static_cast<std::int32_t>(m_KeyCode));
		}
	};

	class KeyReleasedEvent :public KeyEvent {
	public:
		KeyReleasedEvent(const KeyCode keyCode)
			: KeyEvent(keyCode) {

		}

		static EventType GetStaticType() { return EventType::KeyReleasedEvent; }
		virtual EventType getEventType() const override { return GetStaticType(); }
		virtual std::string_view getName() const override { return "KeyReleasedEvent"; }
		std::string toString() const override {
			return "KeyReleasedEvent: " + std::to_string(static_cast<std::int32_t>(m_KeyCode));
		}
	};

	class KeyRepeatEvent : public KeyEvent {
	public:
		KeyRepeatEvent(const KeyCode keyCode, std::int32_t repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) {

		}

		const std::int32_t& getRepeatCount() const { return m_RepeatCount; }

		static EventType GetStaticType() { return EventType::KeyRepeatEvent; }
		virtual EventType getEventType() const override { return GetStaticType(); }
		virtual std::string_view getName() const override { return "KeyRepeatEvent"; }
		std::string toString() const override {
			return "KeyRepeat: " + std::to_string(static_cast<std::int32_t>(m_KeyCode)) + " (repeat count = " + std::to_string(m_RepeatCount) + ")";
		}
	private:
		std::int32_t m_RepeatCount;
	};
}