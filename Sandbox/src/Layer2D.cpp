#include "Layer2D.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Colors.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvents.hpp"
#include "Core/Application.hpp"
#include "Graphics/OpenGL/FrameBuffer.hpp"
#include "Graphics/OpenGL/OpenGLRenderer.hpp"

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
	// fbo test rendering hacks
	// renderer2d does not support fbo based rendering yet
	Hart::FrameBufferSpecification fbo1Spec = {
		.width = 500,
		.height = 300
	};
	int32_t defaultFBOWidth = Hart::Application::Get()->getFrameBufferWidth();
	int32_t defaultFBOHeight = Hart::Application::Get()->getFrameBufferHeight();

	Hart::FrameBuffer fbo{ fbo1Spec };

	{
		fbo.bind();
		Hart::OpenGLRenderer::SetViewPort(0, 0, fbo1Spec.width, fbo1Spec.height);
		Hart::OpenGLRenderer::SetClearColor(Hart::Green);
		m_Camera.setProjection(0.0f, fbo1Spec.width, fbo1Spec.height, 0.0f);

		Hart::Renderer2D::BeginScene(m_Camera);
		Hart::OpenGLRenderer::Clear(
			Hart::RenderClearFlags::ColorBuffer |
			Hart::RenderClearFlags::DepthBuffer |
			Hart::RenderClearFlags::StencilBuffer);

		Hart::Renderer2D::DrawQuad(
			{ fbo1Spec.width / 2.0f, fbo1Spec.height / 2.0f, 0.0f },
			{ 50.0f, 50.0f },
			Hart::Red);

		Hart::Renderer2D::EndScene();
	}

	{
		Hart::OpenGLRenderer::BindDefaultFrameBuffer();
		Hart::OpenGLRenderer::SetViewPort(0, 0, defaultFBOWidth, defaultFBOHeight);
		m_Camera.setProjection(0.0f, defaultFBOWidth, defaultFBOHeight, 0.0f);

		Hart::Renderer2D::BeginScene(m_Camera);

		Hart::OpenGLRenderer::SetClearColor(Hart::DarkGreenishBlue);
		Hart::OpenGLRenderer::Clear(
			Hart::RenderClearFlags::ColorBuffer |
			Hart::RenderClearFlags::DepthBuffer |
			Hart::RenderClearFlags::StencilBuffer);

		Hart::Renderer2D::DrawQuad(
			{ defaultFBOWidth / 2.0f, defaultFBOHeight / 2.0f, 0.0f },
			{ (float)fbo1Spec.width, (float)fbo1Spec.height }, fbo.getColorAttachment());

		Hart::Renderer2D::DrawQuad(
			{ m_MousePosition, 1.0f }, { 30.0f, 30.0f },
			Hart::Vec4::ComponentWiseMultiplication(Hart::Blue, { 1.0f, 1.0f, 1.0f, 0.5f }));
		Hart::Renderer2D::EndScene();
	}
}
