#include "Layer2D.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Colors.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvents.hpp"
#include "Core/Application.hpp"

Layer2D::Layer2D(std::string_view name)
	: Layer(name), m_Camera(0.0f, 960.0f, 540.0f, 0.0f), m_MousePosition(0.0f, 0.0f) {
}

Layer2D::~Layer2D() {
}

void Layer2D::onAttach() {
	HART_CLIENT_INFO("Attached layer: ", getName());
}

void Layer2D::onDetach() {
	HART_CLIENT_INFO("Detached layer: ", getName());
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
	std::shared_ptr<Hart::Texture2D> tex = std::make_shared<Hart::Texture2D>("./res/images/awesomeface.png");
	Hart::Renderer2D::BeginScene(m_Camera);

	Hart::Renderer2D::DrawQuad(
		Hart::Vec2::ScalarMultiply(Hart::Application::Get()->getWindowDimensions(), 0.5f),
		{ 100.0f, 100.0f },
		tex, Hart::Red);
	Hart::Renderer2D::DrawQuad(
		{ m_MousePosition, 1.0f }, { 30.0f, 30.0f },
		Hart::Vec4::ComponentWiseMultiplication(Hart::Blue, { 1.0f, 1.0f, 1.0f, 0.5f }));

	Hart::Renderer2D::EndScene();
}
