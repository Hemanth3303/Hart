#pragma once

#include "Core/Layer.hpp"
#include "Graphics/Camera/OrthographicCamera.hpp"
#include "Graphics/OpenGL/Texture2D.hpp"
#include "Graphics/SpriteSheet.hpp"
#include "Maths/Vec3.hpp"
#include "Graphics/OpenGL/FrameBuffer.hpp"
#include "Graphics/Font.hpp"

#include <string_view>
#include <memory>

class Layer2D : public Hart::Layer {
public:
	Layer2D(std::string_view name);
	~Layer2D();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onEvent(Hart::Event& e) override;
	virtual void update(const float deltaTime) override;
	virtual void render() override;
private:
	Hart::Vec2 m_MousePosition;
	std::shared_ptr<Hart::OrthographicCamera> m_FBOCam, m_ScreenCam;
	std::shared_ptr<Hart::FrameBuffer> m_FBO;
	std::shared_ptr<Hart::Font> m_FontRobotoRegular, m_FontCascadiaMono;
	std::shared_ptr<Hart::Texture2D> m_GrassBlock, m_AwesomeFace;
	std::shared_ptr<Hart::SpriteSheet> m_RPGpack;

	const float m_VirtualScreenWidth = 960.0f;
	const float m_VirtualScreenHeight = 540.0f;
};
