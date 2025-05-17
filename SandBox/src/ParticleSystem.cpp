#include "ParticleSystem.h"
#include "glm/gtx/compatibility.hpp"
ParticleSystem::ParticleSystem(uint32_t maxNumOfParticles) 
    : m_MaxNumberOfParticales(maxNumOfParticles)
{
    m_ParticelPool.resize(maxNumOfParticles);
    m_Index = (uint32_t)m_ParticelPool.size() - 1;
}

void ParticleSystem::Update(JSEngine::TimeStep delta)
{
    for (auto& particle : m_ParticelPool)
    {
        if (!particle.Active) continue;
        if (particle.RemianingLifeTime <= 0)
        {
            particle.Active = false;
            continue;
        }
        
        particle.RemianingLifeTime -= delta;
        
        particle.Position.x +=  particle.Velocity.x *  delta;
        particle.Velocity.y += particle.Acceleration.y * delta;
        particle.Position.y += particle.Velocity.y;
        //CLIENT_INFO("{0}, {1}", particle.Position.y, particle.Velocity.y);

        particle.Rotation += 60.f * delta;

        //particle.Size += (JSEngine::Random::Float() - 0.5f) * 5.f * delta;
        //particle.Rotation += (JSEngine::Random::Float() - 0.5f) * 5.f * delta;

    }

}

void ParticleSystem::OnRender(const JSEngine::Ref<JSEngine::OrthographicCameraController>& camera)
{
    JSEngine::Renderer2D::BeginScene(camera);

    //render particles
    for (auto& particle : m_ParticelPool)
    {
        if (!particle.Active) continue;

        float life = particle.RemianingLifeTime / particle.LifeTime;

        glm::vec4 color = glm::lerp(particle.ColorEnd, particle.ColorBegin, life);
        glm::vec2 size = glm::lerp(particle.SizeEnd, particle.SizeStart, life);
        float rotation = glm::radians(particle.Rotation);
        JSEngine::Renderer2D::DrawRotatedQuad(particle.Position, size, rotation, color, 0);
    }

    JSEngine::Renderer2D::EndScene();
    JSEngine::Renderer2D::Flush();

}


void ParticleSystem::Emit(const ParticleProperty& prop)
{
    auto& particle = m_ParticelPool[m_Index];

    particle.Active    = true;
    particle.Velocity.x = (JSEngine::Random::Float() - 0.5f) * prop.VelocityVariation * prop.Velocity.x;
    particle.Velocity.y = (JSEngine::Random::Float())* prop.Velocity.y;
    particle.Acceleration = prop.Acceleration;

    particle.SizeStart = JSEngine::Random::Float() * prop.SizeVairation * prop.SizeStart;
    particle.SizeEnd   = prop.SizeEnd;

    particle.Position  = prop.Position;

    particle.ColorBegin = prop.ColorBegin;
    particle.ColorEnd = prop.ColorEnd;

    particle.RemianingLifeTime = prop.LifeTime;
    particle.LifeTime = prop.LifeTime;

    particle.Rotation = prop.Rotation;


    m_Index = (m_Index - 1) % m_MaxNumberOfParticales;
}
