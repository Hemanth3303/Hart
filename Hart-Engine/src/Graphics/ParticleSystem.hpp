#pragma once

#include "HartPch.hpp"

#include "Texture2D.hpp"
#include "Camera/OrthographicCamera.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Utils/Random.hpp"

namespace Hart {
	struct ParticleProps {
	public:
		Vec3 position = {};
		Vec2 velocity = {}, velocityVariation = {};
		Vec4 colorBegin = {}, colorEnd = {};
		// minimum rotation angle in degrees of particles, default is 0
		float minAngleD = 0.0f;
		// maximum rotation angle  in degrees of particles, default is 360
		float maxAngleD = 360.0f;
		float sizeBegin = 0.0f, sizeEnd = 0.0f, sizeVariation = 0.0f;
		std::shared_ptr<Texture2D> texture = nullptr;
		float tilingFactor = 1.0f;
		// in seconds
		float lifeTime = 1.0f;
	};

	class ParticleSystem {
	public:
		ParticleSystem(std::uint32_t maxParticles = 10000);

		void update(const float deltaTime);
		// must be called within a Hart::Renderer2D::BeginScene(Camera) and Hart::Renderer2D::EndScene()
		void render();

		void emit(const ParticleProps& particleProps);
	private:
		struct Particle {
			Vec3 position = {};
			Vec2 velocity = {};
			Vec4 colorBegin = {}, colorEnd = {};
			float angleD = 0.0f;
			float sizeBegin = 0.0f, sizeEnd = 0.0f;
			std::shared_ptr<Texture2D> texture = nullptr;
			float tilingFactor = 1.0f;
			// in seconds
			float lifeTime = 1.0f;
			float lifeRemaining = 0.0f;

			bool active = false;
		};
		std::vector<Particle> m_ParticlePool;
		Random m_Random;
		std::uint32_t m_PoolIndex;
	};
}