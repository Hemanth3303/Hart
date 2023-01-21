#pragma once

#include "Event.hpp"
#include "Core/MouseCodes.hpp"

namespace Hart {
	namespace Events {
		class MouseMovedEvent : public Event {
		public:
			MouseMovedEvent(const float x, const float y)
				: m_MouseXPos(x), m_MouseYPos(y) {

			}

			float getXPos() const { return m_MouseXPos; }
			float getYPos() const { return m_MouseYPos; }

			static EventType GetStaticType() { return EventType::MouseMoved; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseMoved"; }
			virtual int32_t getEventCategoryFlags() const override { return (EventCategory::MouseEvent | EventCategory::InputEvent); }
			std::string toString() const override {
				return "MouseMoved: " + std::to_string(m_MouseXPos) + ", " + std::to_string(m_MouseYPos);
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

			static EventType GetStaticType() { return EventType::MouseWheelScrolled; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseWheelScrolled"; }
			virtual int32_t getEventCategoryFlags() const override { return (EventCategory::MouseEvent | EventCategory::InputEvent); }
			std::string toString() const override {
				return "MouseWheelScrolled: " + std::to_string(m_XOffset) + ", " + std::to_string(m_YOffset);
			}
		private:
			float m_XOffset, m_YOffset;
		};

		class MouseButtonEvent : public Event {
		public:
			MouseCode getMouseButton() const { return m_Button; }

			virtual int32_t getEventCategoryFlags() const override { return (EventCategory::MouseEvent | EventCategory::MouseButtonEvent | EventCategory::InputEvent); }
		protected:
			MouseButtonEvent(const MouseCode button)
				: m_Button(button) {

			}
		protected:
			MouseCode m_Button;
		};

		class MouseButtonPressedEvent : public MouseButtonEvent {
		public:
			MouseButtonPressedEvent(const MouseCode button)
				: MouseButtonEvent(button) {

			}

			static EventType GetStaticType() { return EventType::MouseButtonPressed; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseButtonPressed"; }
			std::string toString() const override {
				return "MouseButtonPressed: " + std::to_string(static_cast<int32_t>(m_Button));
			}
		};

		class MouseButtonReleasedEvent : public MouseButtonEvent {
		public:
			MouseButtonReleasedEvent(const MouseCode button)
				: MouseButtonEvent(button) {

			}

			static EventType GetStaticType() { return EventType::MouseButtonReleased; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "MouseButtonReleased"; }
			std::string toString() const override {
				return "MouseButtonReleased: " + std::to_string(static_cast<int32_t>(m_Button));
			}
		};
	}
}