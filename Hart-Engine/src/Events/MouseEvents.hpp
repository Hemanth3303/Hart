/*
* Mousebuttonpress, mousebuttonreleased, mousemoved, mousewheelscrolled
*/

#pragma once

#include "Event.hpp"
#include "Inputs/MouseCodes.hpp"

namespace Hart {
	namespace Events {
		class MouseMovedEvent : public Event {
		public:
			MouseMovedEvent(const float x, const float y)
				: m_MouseXPos(x), m_MouseYPos(y) {

			}

			float getXPos() const { return m_MouseXPos; }
			float getYPos() const { return m_MouseYPos; }

			static EventType GetStaticType() { return EventType::MouseMovedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseMovedEvent"; }
			virtual std::int32_t getEventCategoryFlags() const override { return (EventCategory::MouseEvent | EventCategory::InputEvent); }
			std::string toString() const override {
				return "MouseMovedEvent: " + std::to_string(m_MouseXPos) + ", " + std::to_string(m_MouseYPos);
			}
		private:
			float m_MouseXPos, m_MouseYPos;
		};

		class MouseWheelScrolledEvent : public Event {
		public:
			MouseWheelScrolledEvent(const float xOffset, const float yOffset)
				: m_XOffset(xOffset), m_YOffset(yOffset) {

			}

			float getXOffset() const { return m_XOffset; }
			float getYOffset() const { return m_YOffset; }

			static EventType GetStaticType() { return EventType::MouseWheelScrolledEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseWheelScrolledEvent"; }
			virtual std::int32_t getEventCategoryFlags() const override { return (EventCategory::MouseEvent | EventCategory::InputEvent); }
			std::string toString() const override {
				return "MouseWheelScrolledEvent: " + std::to_string(m_XOffset) + ", " + std::to_string(m_YOffset);
			}
		private:
			float m_XOffset, m_YOffset;
		};

		// Base class for mouse pressed and released events
		class MouseButtonEvent : public Event {
		public:
			Inputs::MouseCode getMouseButton() const { return m_Button; }

			virtual std::int32_t getEventCategoryFlags() const override { return (EventCategory::MouseEvent | EventCategory::MouseButtonEvent | EventCategory::InputEvent); }
		protected:
			MouseButtonEvent(const Inputs::MouseCode button)
				: m_Button(button) {

			}
		protected:
			Inputs::MouseCode m_Button;
		};

		class MouseButtonPressedEvent : public MouseButtonEvent {
		public:
			MouseButtonPressedEvent(const Inputs::MouseCode button)
				: MouseButtonEvent(button) {

			}

			static EventType GetStaticType() { return EventType::MouseButtonPressedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseButtonPressedEvent"; }
			std::string toString() const override {
				return "MouseButtonPressedEvent: " + std::to_string(static_cast<std::int32_t>(m_Button));
			}
		};

		class MouseButtonReleasedEvent : public MouseButtonEvent {
		public:
			MouseButtonReleasedEvent(const Inputs::MouseCode button)
				: MouseButtonEvent(button) {

			}

			static EventType GetStaticType() { return EventType::MouseButtonReleasedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseButtonReleasedEvent"; }
			std::string toString() const override {
				return "MouseButtonReleasedEvent: " + std::to_string(static_cast<std::int32_t>(m_Button));
			}
		};
	}
}