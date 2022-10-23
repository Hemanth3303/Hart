#pragma once

#include "Graphics/Layer.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/BatchRenderer2D.hpp"

#include <memory>

class SandboxLayer : public Hart::Graphics::Layer {
public:
	SandboxLayer(std::shared_ptr<Hart::Graphics::Shader> shader, const Hart::Maths::Mat4& projectionMatrix)
		: Layer(std::make_shared<Hart::Graphics::BatchRenderer2D>(), shader, projectionMatrix) {

	}
	~SandboxLayer() {

	}
};