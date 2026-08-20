#include "Layer2D.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Graphics/Colors.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvents.hpp"

#include "Maths/Mat4.hpp"

Layer2D::Layer2D(const std::string& name)
	: Layer(name), m_Camera(0.0f, 960.0f, 540.0f, 0.0f), m_MousePosition(0.0f, 0.0f) {
}

Layer2D::~Layer2D() {
}

void Layer2D::onAttach() {
	HART_CLIENT_INFO("Attached layer: ", getName());
}

void Layer2D::onDetach() {
	HART_CLIENT_INFO(std::string("Detached layer: ") + getName());
}
void Layer2D::onEvent(Hart::Event& e) {
	Hart::EventDispatcher eventDispatcher(e);

	eventDispatcher.dispatch<Hart::MouseMovedEvent>([this](Hart::MouseMovedEvent& e) {
		m_MousePosition.x = e.getXPosition();
		m_MousePosition.y = e.getYPosition();

		return true;
	});
}

void Layer2D::update(const float deltaTime) {
}

void Layer2D::render() {
	// Hart::Renderer2D::BeginScene(m_Camera);

	// Hart::Renderer2D::DrawQuad(m_MousePosition, { 30.0f, 30.0f }, Hart::Blue);

	// Hart::Renderer2D::EndScene();
}
