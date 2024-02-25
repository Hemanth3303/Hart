#pragma once

#include "Hart.hpp"

class Layer2D : public Hart::Layer {
public:
	Layer2D(const std::string& name = "Layer2D");
	~Layer2D();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onEvent(Hart::Event& e) override;
	virtual void update(const float deltaTime) override;
	virtual void render() override;
private:
	std::shared_ptr<Hart::Texture2D> m_GrassTex, m_EmojiTex;
	std::shared_ptr<Hart::SpriteSheet> m_SpriteSheet;
	std::shared_ptr<Hart::OrthographicCameraController> m_CameraController;
	std::shared_ptr<Hart::Sound> pickupSound;
	std::shared_ptr<Hart::Music> criticalTheme;
	Hart::Random m_Rd;
	Hart::ParticleProps m_Particle;
	Hart::ParticleSystem m_ParticleSystem;
	Hart::Vec3 m_MousePos = { 0.0f, 0.0f, 1.0f };
};