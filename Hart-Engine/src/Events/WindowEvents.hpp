/*
* WindowResized, windowclosed, windowfocuslost, windowfocusgained, windowmoved
*/

#pragma once

#include "Event.hpp"

namespace Hart {
	namespace Events {
		class WindowResizedEvent :public Event {
		public:
			WindowResizedEvent(uint32_t width, uint32_t height)
				: m_Width(width), m_Height(height) {

			}

			inline uint32_t getWidth() const { return m_Width; }
			inline uint32_t getHeight() const { return m_Height; }

			static EventType GetStaticType() { return EventType::WindowResized; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowResized"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }

			std::string toString() const override {
				return ("WindowResized: " + std::to_string(m_Width) + ", " + std::to_string(m_Height));
			}

		private:
			uint32_t m_Width, m_Height;
		};

		class WindowClosedEvent : public Event {
		public:
			WindowClosedEvent() = default;

			static EventType GetStaticType() { return EventType::WindowClosed; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowClosed"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }
		};

		class WindowMovedEvent : public Event {
		public:
			WindowMovedEvent() = default;

			static EventType GetStaticType() { return EventType::WindowMoved; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowMoved"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }
		};

		class WindowFocusGainedEvent : public Event {
		public:
			WindowFocusGainedEvent() = default;

			static EventType GetStaticType() { return EventType::WindowFocusGained; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowFocusGained"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }
		};

		class WindowFocusLostEvent : public Event {
		public:
			WindowFocusLostEvent() = default;

			static EventType GetStaticType() { return EventType::WindowFocusLost; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowFocusLost"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }
		};
	}
}