#pragma once

#include "Core/Layer.hpp"
#include "Graphics/Camera/OrthographicCamera.hpp"
#include "Maths/Vec3.hpp"
#include "Graphics/OpenGL/FrameBuffer.hpp"

#include <string_view>

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
	Hart::OrthographicCamera m_Camera;
	Hart::FrameBuffer m_FBO;
};
