#pragma once

#include "Hart.hpp"

class Layer3D : public Hart::Layer {
public:
	Layer3D(const std::string& name = "Layer3D");
	~Layer3D();

	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onEvent(Hart::Event& e) override;
	bool onMouseMoved(Hart::MouseMovedEvent& e);
	bool onMouseWheelScrolled(Hart::MouseWheelScrolledEvent& e);
	virtual void update(const float deltaTime) override;
	virtual void render() override;
private:
	std::shared_ptr<Hart::VertexArray> m_Vao;
	std::shared_ptr<Hart::Shader> m_Shader;
	std::shared_ptr<Hart::PerspectiveCamera> m_Camera;
	std::shared_ptr<Hart::Texture2D> m_GrassTex;

	float angle = 0.0f;
	bool firstMouse = true;
	float lastX = 960.0f / 2.0;
	float lastY = 540.0 / 2.0;
	float fovD = 45.0f;
	float m_AspectRatio = 0.0f;

	std::vector<Hart::Vec3> cubePositions = {
		Hart::Vec3(0.0f,  0.0f,  0.0f),
		Hart::Vec3(2.0f,  3.0f, -1.0f),
		Hart::Vec3(-1.5f, -2.2f, -2.5f),
		Hart::Vec3(-3.8f, -2.0f, -12.3f),
		Hart::Vec3(2.4f, -0.4f, -3.5f),
		Hart::Vec3(-1.7f,  3.0f, -7.5f),
		Hart::Vec3(1.3f, -2.0f, -2.5f),
		Hart::Vec3(1.5f,  2.0f, -2.5f),
		Hart::Vec3(1.5f,  0.2f, -1.5f),
		Hart::Vec3(-1.3f,  1.0f, -1.5f)
	};
};