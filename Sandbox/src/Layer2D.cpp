#include "Layer2D.hpp"

#undef DrawText

Layer2D::Layer2D(const std::string& name)
	: Layer(name), m_ParticleSystem(1'000'000) {
}

Layer2D::~Layer2D() {

}

void Layer2D::onAttach() {
	HART_CLIENT_LOG(std::string("Attached layer: ") + getName());

	Hart::Texture2DSpecification pixelArtTextureSpec;
	pixelArtTextureSpec.magFilter = Hart::TextureMagFilter::Nearest;

	m_GrassTex = std::make_shared<Hart::Texture2D>("res/images/grass_block.png", pixelArtTextureSpec);
	m_EmojiTex = std::make_shared<Hart::Texture2D>("res/images/awesomeface.png");
	m_SpriteSheet = std::make_shared<Hart::SpriteSheet>("res/images/RPGpack_sheet_2X.png", Hart::Vec2(128, 128), pixelArtTextureSpec);
	m_Font1 = std::make_shared<Hart::Font>("res/fonts/Roboto-Regular.ttf", 48.0f);
	m_Font2 = std::make_shared<Hart::Font>("res/fonts/CascadiaCode.ttf", 32.0f);

	m_CameraController = std::make_shared<Hart::DefaultOrthographicCameraController>(960.0f, 540.0f);

	m_Particle.colorBegin = Hart::FireRed;
	m_Particle.colorEnd = Hart::White;
	m_Particle.sizeBegin = 0.08f, m_Particle.sizeVariation = 0.001f, m_Particle.sizeEnd = 0.0f;
	m_Particle.lifeTime = 2.0f;
	m_Particle.velocity = { m_Rd.getRandomFloat(-1.0f, 1.0f), m_Rd.getRandomFloat(-1.0f, 1.0f) };
	m_Particle.velocityVariation = { m_Rd.getRandomFloat(-2.0f, 2.0f),  m_Rd.getRandomFloat(-2.0f, 2.0f) };
	m_Particle.position = { 0.0f, 0.0f, 1.0f };

	pickupSound = std::make_shared<Hart::Sound>("res/sfx/pickup.wav");
	criticalTheme = std::make_shared<Hart::Music>("res/music/CriticalTheme.wav");

	//Hart::AudioManager::PlaySound(pickupSound);
	//Hart::AudioManager::PlayMusic(criticalTheme);
}

void Layer2D::onDetach() {
	HART_CLIENT_LOG(std::string("Detached layer: ") + getName());
}

void Layer2D::onEvent(Hart::Event& e) {
	//HART_CLIENT_LOG(e);
	m_CameraController->onEvent(e);
}

void Layer2D::update(const float deltaTime) {
	//Hart::ScopedTimer sp("Layer2D Update Loop");

	auto [x, y] = Hart::InputManager::GetMousePosition();
	std::int32_t width = Hart::Application::Get()->getWindowWidth();
	std::int32_t height = Hart::Application::Get()->getWindowHeight();

	Hart::OrthographicCameraBounds bounds = m_CameraController->getBounds();
	Hart::Vec3 position = m_CameraController->getCamera().getPosition();
	x = (x / width) * bounds.getWidth() - bounds.getWidth() * 0.5f;
	y = bounds.getHeight() * 0.5f - (y / height) * bounds.getHeight();
	m_Particle.position = { x + position.x, y + position.y , 1.0f };

	m_MousePos.x = x;
	m_MousePos.y = y;

	if (Hart::InputManager::IsMouseButtonPressed(Hart::MouseCode::Left)) {
		m_ParticleSystem.emit(m_Particle);
		//Hart::AudioManager::PlaySound(pickupSound);
		//Hart::AudioManager::PuaseAllAudio();
	}
	if (Hart::InputManager::IsMouseButtonPressed(Hart::MouseCode::Right)) {
		//Hart::AudioManager::ResumeAlludio();
	}

	m_CameraController->update(deltaTime);
	m_ParticleSystem.update(deltaTime);
}

void Layer2D::render() {
	//Hart::ScopedTimer sp("Layer2D Render Loop");
	static std::string fps, drawCalls, quads, quadVerts, quadInds, textQuads, textQuadVerts, textQuadInds;

	Hart::Renderer2D::ResetStats();
	Hart::Renderer2D::BeginScene(m_CameraController->getCamera());
	{

		Hart::Renderer2D::DrawLine({ -0.5f, -0.5f }, { 0.5f, -0.5f }, Hart::Red);
		Hart::Renderer2D::DrawLine({ 0.5f, -0.5f }, { 0.0f,  0.5f }, Hart::Blue);
		Hart::Renderer2D::DrawLine({ 0.0f,  0.5f }, { -0.5f, -0.5f }, Hart::Green);

		Hart::Renderer2D::DrawLine({ 0.0f, 0.0f, 1.0f }, m_MousePos, Hart::Cyan);

		Hart::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, m_GrassTex);
		Hart::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 0.5f, 0.5f }, m_EmojiTex);
		Hart::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.5f, 0.5f }, m_SpriteSheet, { 0, 0 });

		Hart::Mat4 transform = Hart::Mat4::Translate({ 0.9f, 0.6f }) * Hart::Mat4::Rotate(67.0f, { 0.0f, 0.0f, 1.0f }) * Hart::Mat4::Scale({ 0.25, 0.45 });

		Hart::Renderer2D::DrawQuad(transform, Hart::Gold);
		Hart::Renderer2D::DrawQuad({ 0.0f, 0.9f }, { 0.1f, 0.1f }, Hart::White);
		Hart::Renderer2D::DrawQuad({ -0.9f, -0.9f }, { 0.1f, 0.1f }, Hart::Red);

		Hart::Renderer2D::SetFont(m_Font1);
		Hart::Renderer2D::DrawText("Hello, World!", { 0.0f, 0.0f, 1.0f }, 2.0f, Hart::NormalizeRGB255({ 240.0f,0.0f,255.0f }));

		Hart::Renderer2D::DrawText("FPS: " + fps, { -1.6f, 0.8f, 1.0f }, 0.7f, Hart::White);
		Hart::Renderer2D::DrawText("No of DrawCalls: " + drawCalls, { -1.6f, 0.75f, 1.0f }, 0.7f, Hart::White);
		Hart::Renderer2D::DrawText("No of Quads: " + quads, { -1.6f, 0.7f, 1.0f }, 0.7f, Hart::White);
		Hart::Renderer2D::DrawText("No of Quad Vertices: " + quadVerts, { -1.6f, 0.65f, 1.0f }, 0.7f, Hart::White);
		Hart::Renderer2D::DrawText("No of Quad Indices: " + quadInds, { -1.6f, 0.6f, 1.0f }, 0.7f, Hart::White);
		Hart::Renderer2D::DrawText("No of TextQuads: " + textQuads, { -1.6f, 0.55f, 1.0f }, 0.7f, Hart::White);
		Hart::Renderer2D::DrawText("No of TextQuad Vertices: " + textQuadVerts, { -1.6f, 0.5f, 1.0f }, 0.7f, Hart::White);
		Hart::Renderer2D::DrawText("No of TextQuad Indices: " + textQuadInds, { -1.6f, 0.45f, 1.0f }, 0.7f, Hart::White);

		m_ParticleSystem.render();
	}
	Hart::Renderer2D::EndScene();

	fps = std::to_string(Hart::Application::Get()->getCurrentFPS());
	drawCalls = std::to_string(Hart::Renderer2D::GetNumberOfDrawCalls());
	quads = std::to_string(Hart::Renderer2D::GetNumberOfQuads());
	quadVerts = std::to_string(Hart::Renderer2D::GetNumberOfQuadVertices());
	quadInds = std::to_string(Hart::Renderer2D::GetNumberOfQuadIndices());
	textQuads = std::to_string(Hart::Renderer2D::GetNumberOfTextQuads());
	textQuadVerts = std::to_string(Hart::Renderer2D::GetNumberOfTextQuadVertices());
	textQuadInds = std::to_string(Hart::Renderer2D::GetNumberOfTextQuadIndices());
}
