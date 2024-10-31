#include "Layer2D.hpp"

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
	//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(Hart::Application::Get()->getCurrentFPS()));

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
	Hart::Renderer2D::ResetStats();
	Hart::Renderer2D::BeginScene(m_CameraController->getCamera());

	Hart::Renderer2D::DrawLine({ -0.5f, -0.5f }, { 0.5f, -0.5f }, Hart::Red);
	Hart::Renderer2D::DrawLine({ 0.5f, -0.5f }, { 0.0f,  0.5f }, Hart::Blue);
	Hart::Renderer2D::DrawLine({ 0.0f,  0.5f }, { -0.5f, -0.5f }, Hart::Green);

	Hart::Renderer2D::DrawLine({ 0.0f, 0.0f, 1.0f }, m_MousePos, Hart::Cyan);

	Hart::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, m_GrassTex);
	Hart::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 0.5f, 0.5f }, m_EmojiTex);
	Hart::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.5f, 0.5f }, m_SpriteSheet, { 0, 0 });

	Hart::Mat4 transform = Hart::Mat4::Translate({ 0.9f, 0.6f }) * Hart::Mat4::Rotate(67.0f, { 0.0f, 0.0f, 1.0f }) * Hart::Mat4::Scale({ 0.25, 0.45 });

	Hart::Renderer2D::DrawQuad(transform, Hart::Gold);

	m_ParticleSystem.render();

	Hart::Renderer2D::EndScene();
	//HART_CLIENT_TRACE("No of drawcalls: " + std::to_string(Hart::Renderer2D::GetNumberOfDrawCalls()));
	//HART_CLIENT_TRACE("No of quads: " + std::to_string(Hart::Renderer2D::GetNumberOfQuads()));
	//HART_CLIENT_TRACE("No of quad vertices: " + std::to_string(Hart::Renderer2D::GetNumberOfQuadVertices()));
	//HART_CLIENT_TRACE("No of quad indices: " + std::to_string(Hart::Renderer2D::GetNumberOfQuadIndices()));
	//HART_CLIENT_TRACE("No of lines: " + std::to_string(Hart::Renderer2D::GetNumberOfLines()));
	//HART_CLIENT_TRACE("No of line vertices: " + std::to_string(Hart::Renderer2D::GetNumberOfLineVertices()));
}
