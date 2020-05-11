#pragma once
#include <vector>
#include <JSEngine.h>
#include <glm/glm.hpp>



struct ParticleProperty
{
    glm::vec2 Velocity;
    glm::vec2 Position;

    glm::vec2 SizeStart;
    glm::vec2 SizeEnd;
    glm::vec4 ColorBegin;
    glm::vec4 ColorEnd;

    float VelocityVariation;
    float SizeVairation;

    glm::vec2 Acceleration;

    float Rotation;
    float LifeTime = 1.f;
    bool Active = false;
};


class ParticleSystem
{

public:
    ParticleSystem(uint32_t maxNumOfParticles);
    void Update(JSEngine::TimeStep delta);
    void OnRender(const JSEngine::Ref<JSEngine::OrthographicCameraController>& camera);
    void Emit(const ParticleProperty& prop);

private:

    struct Particle
    {
        glm::vec2 Velocity;
        glm::vec2 Acceleration;
        glm::vec2 Position;

        glm::vec2 SizeStart;
        glm::vec2 SizeEnd;
        glm::vec4 ColorBegin;
        glm::vec4 ColorEnd;


        float Rotation;
        float LifeTime = 1.f;
        float RemianingLifeTime;
        bool Active = false;
    };


    std::vector<Particle> m_ParticelPool;
    uint32_t m_Index;
    uint32_t m_MaxNumberOfParticales;
    bool m_StartRender = false;

};