#include "Layer2D.hpp"
#include "Utils/Logger.hpp"
#include "Graphics/Colors.hpp"
#include "Graphics/Renderer2D/Renderer2D.hpp"
#include "Events/EventDispatcher.hpp"
#include "Events/MouseEvents.hpp"
#include "Core/Application.hpp"
#include "Core/Assert.hpp"

Layer2D::Layer2D(std::string_view name)
	: Layer(name), m_MousePosition(0.0f, 0.0f) {

	m_FBO = std::make_shared<Hart::FrameBuffer>(Hart::FrameBufferSpecification{ 500, 300 });
	m_FBOCam = std::make_shared<Hart::OrthographicCamera>(0.0, 500.0f, 300.0f, 0.0f);
	m_ScreenCam = std::make_shared<Hart::OrthographicCamera>(0.0, 960.0f, 540.0f, 0.0f);

	Hart::Texture2DSpecification pixelArtTextureSpec = {
		.magFilter = Hart::TextureMagFilter::Nearest,
		.minFilter = Hart::TextureMinFilter::NearestNearest,
		.generateMipMaps = true,
	};

	Hart::Texture2DSpecification normalTextureSpec = {
		.magFilter = Hart::TextureMagFilter::Linear,
		.minFilter = Hart::TextureMinFilter::LinearLinear,
		.generateMipMaps = true,
	};

	m_AwesomeFace = std::make_shared<Hart::Texture2D>("./res/images/awesomeface.png", normalTextureSpec);
	m_GrassBlock = std::make_shared<Hart::Texture2D>("./res/images/grass_block.png", pixelArtTextureSpec);
	m_RPGpack = std::make_shared<Hart::SpriteSheet>("./res/images/RPGpack_sheet_2X.png", Hart::Vec2{ 128.0f, 128.0f }, pixelArtTextureSpec);

	m_Font = std::make_shared<Hart::Font>("./res/fonts/Roboto-Regular.ttf");
}

Layer2D::~Layer2D() {
}

void Layer2D::onAttach() {
	HART_CLIENT_INFO("Attached layer: ", getName());

	Hart::Renderer2D::SetFont(m_Font);
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
		Hart::Renderer2D::BeginRenderPass({
			.fbo = m_FBO,
			.camera = m_FBOCam,
			.clearColor = Hart::Green,
		});

		Hart::Renderer2D::DrawQuad(
			{ m_FBO->getSpec().width / 2.0f, m_FBO->getSpec().height / 2.0f, 0.0f },
			{ 50.0f, 50.0f },
			Hart::Red);

		Hart::Renderer2D::DrawText(
			"Hello, World\nOmg!",
			{ 150.0f, 80.0f, 1.0f },
			0.7f, Hart::Magenta);

		Hart::Renderer2D::DrawQuad(
			{ 300.0f, 250.0f, 1.0f },
			{ 50.0f, 50.0f },
			m_GrassBlock);

		Hart::Renderer2D::DrawQuad(
			{ 100.0f, 250.0f, 1.0f },
			{ 50.0f, 50.0f },
			m_RPGpack,
			{ 1, 6 });

		Hart::Renderer2D::EndRenderPass();
	}

	{
		Hart::Renderer2D::BeginRenderPass({
			.fbo = Hart::FrameBuffer::GetDefaultFrameBuffer(),
			.camera = m_ScreenCam,
			.clearColor = Hart::DarkGreenishBlue,
		});

		Hart::Renderer2D::DrawQuad(
			{ (float)m_FBO->getSpec().width / 2.0f, (float)m_FBO->getSpec().height / 2.0f, 0.0f },
			{ (float)m_FBO->getSpec().width, (float)m_FBO->getSpec().height }, 0.0f,
			m_FBO->getColorAttachment(), Hart::Gold);

		Hart::Renderer2D::DrawQuad(
			{ (float)m_FBO->getSpec().width + (float)m_FBO->getSpec().width / 2.0f, (float)m_FBO->getSpec().height / 2.0f, 0.0f },
			{ (float)m_FBO->getSpec().width, (float)m_FBO->getSpec().height }, 0.0f,
			m_FBO->getColorAttachment(), Hart::Gray);

		Hart::Renderer2D::DrawQuad(
			{ (float)m_FBO->getSpec().width + (float)m_FBO->getSpec().width / 2.0f, (float)m_FBO->getSpec().height + (float)m_FBO->getSpec().height / 2.0f, 0.0f },
			{ (float)m_FBO->getSpec().width / 2.0f, (float)m_FBO->getSpec().height / 2.0f }, 0.0f,
			m_FBO->getDepthStencilAttachment());

		Hart::Renderer2D::DrawText(
			"Test Text\nAnd A New Line",
			{ 20.0f, 350.0f, 0.0f },
			0.5f, Hart::Blue);

		Hart::Renderer2D::DrawQuad(
			{ 200.0f, 450.0f, 0.0f },
			{ 100.0f, 100.0f },
			m_AwesomeFace);

		Hart::Renderer2D::DrawQuad(
			{ 400.0f, 450.0f, 0.0f },
			{ 150.0f, 150.0f },
			m_GrassBlock);

		Hart::Renderer2D::DrawQuad(
			{ 550.0f, 450.0f, 0.0f },
			{ 50.0f, 50.0f },
			m_RPGpack,
			{ 1, 6 });

		Hart::Renderer2D::DrawQuad(
			{ m_MousePosition, 1.0f }, { 30.0f, 30.0f },
			Hart::Vec4::ComponentWiseMultiplication(Hart::Blue, { 1.0f, 1.0f, 1.0f, 0.5f }));
		Hart::Renderer2D::EndRenderPass();
	}
}
