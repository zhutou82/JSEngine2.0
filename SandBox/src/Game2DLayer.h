#pragma once
#include <JSEngine.h>
#include <vector>
#include "ParticleSystem.h"

class Game2DLayer : public JSEngine::Layer
{

public:
    Game2DLayer();
    virtual ~Game2DLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(JSEngine::TimeStep delta) override;
    virtual void OnRenderUpdate(JSEngine::TimeStep delta) override;
    virtual void OnEvent(JSEngine::Event& e) override;

private:

    JSEngine::Ref<JSEngine::OrthographicCameraController> m_Camera;
    JSEngine::Ref<JSEngine::Shader> m_Shader2D;

    std::vector<JSEngine::Ref<JSEngine::Mesh>>       m_MeshVec;
    JSEngine::Ref<JSEngine::SceneData2D>     m_SceneData;

    JSEngine::Ref<JSEngine::VertexArray> m_VAO;

    ParticleSystem m_ParticalSystem;
    ParticleProperty m_ParticleProp;

    JSEngine::Ref<JSEngine::Texture> m_AwesomeFace;
    JSEngine::Ref<JSEngine::Texture> m_Bobo;
    JSEngine::Ref<JSEngine::Texture> m_Robot;

    JSEngine::Ref<JSEngine::SubTexture2D> m_RobotSub;

    JSEngine::Ref<JSEngine::Animation2D> m_Animation;


};