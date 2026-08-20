#pragma once

#include "Core/Layer.hpp"
#include "Graphics/Camera/OrthographicCamera.hpp"
#include "Maths/Vec3.hpp"

class Layer2D : public Hart::Layer {
public:
	Layer2D(const std::string& name);
	~Layer2D();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onEvent(Hart::Event& e) override;
	virtual void update(const float deltaTime) override;
	virtual void render() override;
private:
	Hart::Vec2 m_MousePosition;
};
