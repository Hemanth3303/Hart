#include "HartPch.hpp"
#include "ParticleSystem.hpp"
#include "../Renderer/Renderer2D.hpp"

namespace Hart {
	namespace Graphics {
		ParticleSystem::ParticleSystem(std::uint32_t maxParticles)
			: m_PoolIndex(maxParticles-1) {
			m_ParticlePool.resize(maxParticles);
		}

		void ParticleSystem::update(const float deltaTime) {
			for (auto& particle : m_ParticlePool) {
				if (!particle.active)
					continue;

				if (particle.lifeRemaining <= 0.0f) {
					particle.active = false;
					continue;
				}

				particle.lifeRemaining -= deltaTime;
				particle.velocity.scalarMultiply(deltaTime);
				particle.position += particle.velocity;
				particle.rotation += 0.01f * deltaTime;
			}
		}

		void ParticleSystem::render() {
			for (auto& particle : m_ParticlePool) {
				if (!particle.active)
					continue;

				// Fade away particles
				float life = particle.lifeRemaining / particle.lifeTime;
				Maths::Vec4 color = Maths::Vec4::lerp(particle.colorEnd, particle.colorBegin, life);

				float size = static_cast<float>(Maths::lerp(particle.sizeEnd, particle.sizeBegin, life));

				if (particle.texture == nullptr) {
					Renderer2D::DrawQuad(particle.position, Maths::Vec2(size, size), particle.rotation, color);
				}
				else {
					Renderer2D::DrawQuad(particle.position, Maths::Vec2(size, size), particle.rotation, particle.texture, color, particle.tilingFactor);
				}
			}
		}
		
		void ParticleSystem::emit(const ParticleProps& particleProps) {
			Particle& particle = m_ParticlePool[m_PoolIndex];
			particle.active = true;

			// position
			particle.position = particleProps.position;

			// rotation
			particle.rotation = m_Random.getRandomFloat(0.0f, 360.0f);

			// velocity
			particle.velocity = particleProps.velocity;
			particle.velocity.x += particleProps.velocityVariation.x * m_Random.getRandomFloat(-0.5f, 0.5f);
			particle.velocity.y += particleProps.velocityVariation.y * m_Random.getRandomFloat(-0.5f, 0.5f);

			// color
			particle.colorBegin = particleProps.colorBegin;
			particle.colorEnd = particleProps.colorEnd;

			// lifetime
			particle.lifeTime = particleProps.lifeTime;
			particle.lifeRemaining = particleProps.lifeTime;

			// size
			particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * m_Random.getRandomFloat(-0.5f, 0.5f);
			particle.sizeEnd = particleProps.sizeEnd;

			// texture
			particle.texture = particleProps.texture;
			particle.tilingFactor = particleProps.tilingFactor;

			m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
		}
	}
}