#pragma once

#include "Hart.hpp"

using namespace Hart;
using namespace Hart::Graphics;
using namespace Hart::Maths;
using namespace Hart::Events;
using namespace Hart::Inputs;
using namespace Hart::Utils;

class Layer3D : public Layer {
private:
	std::array<float, 42> m_Vertices = {
		//position              // color                 //texture coords
		1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	   -1.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	};
	std::array<std::uint32_t, 6> m_Indices = {
		0, 1, 3,
		1, 2, 3,
	};
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<Texture2D> m_Tex1, m_Tex2;
	ShaderLibrary m_ShaderLibrary;
	OrthographicCameraController m_CameraController;
public:
	Layer3D(const std::string& name = "Layer3D")
		:Layer(name), m_CameraController(960.0f / 540.0f) {

		m_CameraController.setRotationSpeed(45);

		m_ShaderLibrary.loadShader("textureShader", "res/shaders/textureVert.glsl", "res/shaders/textureFrag.glsl");
		m_Tex1 = std::make_shared<Texture2D>("res/images/grass_block.png", MagFilter::Nearest);
		m_Tex2 = std::make_shared<Texture2D>("res/images/awesomeface.png", MagFilter::Linear);

		BufferLayout layout = {
			{ ShaderDataType::Float3, "aPosition" },
			{ ShaderDataType::Float4, "aColor" },
			{ ShaderDataType::Float2, "aTexCoord" }
		};

		m_VertexArray = std::make_shared<VertexArray>();
		m_VertexArray->bind();

		std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(m_Vertices.data(), (std::uint32_t)sizeof(m_Vertices));
		vbo->setLayout(layout);
		m_VertexArray->addVertexBuffer(vbo);

		std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>(m_Indices.data(), 6);
		m_VertexArray->setIndexBuffer(ibo);

		m_VertexArray->unbind();

		m_ShaderLibrary.getShader("textureShader")->bind();
		m_ShaderLibrary.getShader("textureShader")->setUniform("uTexture", m_Tex1->getSlot());
		m_ShaderLibrary.getShader("textureShader")->unbind();

		m_CameraController.setMovementSpeed(10);
	}

	~Layer3D() {

	}

	void onAttach() override {
		HART_CLIENT_LOG(std::string("Attached layer: ") + getName());
	}
	
	void onDetach() override {
		HART_CLIENT_LOG(std::string("Detached layer: ") + getName());
	}

	void onEvent(Event& e) override {
		//HART_CLIENT_LOG(e);
		m_CameraController.onEvent(e);
	}

	void update(const float deltaTime) override {
		//HART_CLIENT_LOG("DeltaTime: " + std::to_string(deltaTime) + " | FPS: " + std::to_string(getCurrentFPS()));
		m_CameraController.update(deltaTime);
	}

	void render() override {

		Mat4 scale = Mat4::scale(Vec3(0.15f));

		RenderCommand::SetClearColor({ 18.0f, 18.0f, 18.0f, 1.0f });

		Renderer3D::BeginScene(m_CameraController.getCamera());
		m_Tex1->bind();
		Renderer3D::Submit(m_VertexArray, m_ShaderLibrary.getShader("textureShader"), Mat4::indentity());
		m_Tex2->bind();
		Renderer3D::Submit(m_VertexArray, m_ShaderLibrary.getShader("textureShader"), Mat4::translate(Vec3(1.5, 0, 1)));
		Renderer3D::EndScene();
	}
};