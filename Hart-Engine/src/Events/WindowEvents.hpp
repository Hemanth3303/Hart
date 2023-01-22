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

			static EventType GetStaticType() { return EventType::WindowResizedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowResizedEvent"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }

			std::string toString() const override {
				return ("WindowResizedEvent: " + std::to_string(m_Width) + ", " + std::to_string(m_Height));
			}

		private:
			uint32_t m_Width, m_Height;
		};

		class WindowClosedEvent : public Event {
		public:
			WindowClosedEvent() = default;

			static EventType GetStaticType() { return EventType::WindowClosedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowClosedEvent"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }
		};

		class WindowMovedEvent : public Event {
		public:
			WindowMovedEvent(float xpos, float ypos) 
				: m_Xpos(xpos), m_Ypos(ypos) {

			}

			static EventType GetStaticType() { return EventType::WindowMovedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowMovedEvent"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }

			std::string toString() const override {
				return ("WindowMovedEvent: " + std::to_string(m_Xpos) + ", " + std::to_string(m_Ypos));
			}
		private:
			float m_Xpos, m_Ypos;
		};

		class WindowFocusGainedEvent : public Event {
		public:
			WindowFocusGainedEvent() = default;

			static EventType GetStaticType() { return EventType::WindowFocusGainedEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowFocusGained"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }
		};

		class WindowFocusLostEvent : public Event {
		public:
			WindowFocusLostEvent() = default;

			static EventType GetStaticType() { return EventType::WindowFocusLostEvent; }
			virtual EventType getEventType() const override { return GetStaticType(); }
			virtual std::string_view getName() const override { return "WindowFocusLost"; }
			virtual int32_t getEventCategoryFlags() const override { return EventCategory::WindowEvent; }
		};
	}
}