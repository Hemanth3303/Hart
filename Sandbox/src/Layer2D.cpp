#include "Layer2D.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Colors.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvents.hpp"
#include "Core/Application.hpp"

Layer2D::Layer2D(std::string_view name)
	: Layer(name), m_Camera(0.0f, 960.0f, 540.0f, 0.0f),
	  m_MousePosition(0.0f, 0.0f), m_FBO({ .width = 500, .height = 300 }) {
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
	int32_t defaultFBOWidth = Hart::Application::Get()->getFrameBufferWidth();
	int32_t defaultFBOHeight = Hart::Application::Get()->getFrameBufferHeight();

	{
		m_Camera.setProjection(0.0f, m_FBO.getSpec().width, m_FBO.getSpec().height, 0.0f);

		Hart::Renderer2D::BeginRenderPass({
			.fbo = m_FBO,
			.camera = m_Camera,
			.clearColor = Hart::Green,
		});

		Hart::Renderer2D::DrawQuad(
			{ m_FBO.getSpec().width / 2.0f, m_FBO.getSpec().height / 2.0f, 0.0f },
			{ 50.0f, 50.0f },
			Hart::Red);

		Hart::Renderer2D::EndRenderPass();
	}

	{
		m_Camera.setProjection(0.0f, defaultFBOWidth, defaultFBOHeight, 0.0f);
		Hart::Renderer2D::BeginRenderPass({
			.fbo = Hart::FrameBuffer::GetDefaultFrameBuffer(),
			.camera = m_Camera,
			.clearColor = Hart::DarkGreenishBlue,
		});

		Hart::Renderer2D::DrawQuad(
			{ defaultFBOWidth / 2.0f, defaultFBOHeight / 2.0f, 0.0f },
			{ (float)m_FBO.getSpec().width, (float)m_FBO.getSpec().height }, 30.0f,
			m_FBO.getColorAttachment(), {1.0f, 0.3f, 0.0f, 0.7f});

		Hart::Renderer2D::DrawQuad(
			{ m_MousePosition, 1.0f }, { 30.0f, 30.0f },
			Hart::Vec4::ComponentWiseMultiplication(Hart::Blue, { 1.0f, 1.0f, 1.0f, 0.5f }));
		Hart::Renderer2D::EndRenderPass();
	}
}
