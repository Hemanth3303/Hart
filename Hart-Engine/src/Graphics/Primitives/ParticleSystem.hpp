#pragma once

#include "HartPch.hpp"

#include "../Primitives/Texture2D.hpp"
#include "../Camera/OrthographicCamera.hpp"
#include "Maths/Vec2.hpp"
#include "Maths/Vec3.hpp"
#include "Maths/Vec4.hpp"
#include "Utils/Random.hpp"

namespace Hart {
	namespace Graphics {
		struct ParticleProps {
		public:
			Maths::Vec3 position;
			Maths::Vec2 velocity, velocityVariation;
			Maths::Vec4 colorBegin, colorEnd;
			float sizeBegin, sizeEnd, sizeVariation;
			std::shared_ptr<Texture2D> texture = nullptr;
			float tilingFactor = 1.0f;
			// in seconds
			float lifeTime = 1.0f;
		};

		class ParticleSystem {
		public:
			ParticleSystem(std::uint32_t maxParticles = 10000);

			void update(const float deltaTime);
			void render();

			void emit(const ParticleProps& particleProps);
		private:
			struct Particle {
				Maths::Vec3 position = {};
				Maths::Vec2 velocity = {};
				Maths::Vec4 colorBegin = {}, colorEnd = {};
				float rotation = 0.0f;
				float sizeBegin, sizeEnd;
				std::shared_ptr<Texture2D> texture = nullptr;
				float tilingFactor = 1.0f;
				// in seconds
				float lifeTime = 1.0f;
				float lifeRemaining = 0.0f;

				bool active = false;
			};
			std::vector<Particle> m_ParticlePool;
			Utils::Random m_Random;
			std::uint32_t m_PoolIndex;
		};
	}
}