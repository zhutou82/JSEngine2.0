#pragma once
#include <JSEngine.h>

class Game3DLayer : public JSEngine::Layer
{
public:
    Game3DLayer();
    virtual ~Game3DLayer() {}

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(JSEngine::TimeStep delta) override;
    virtual void OnRenderUpdate(JSEngine::TimeStep delta) override;
    virtual void OnEvent(JSEngine::Event& e) override;

private:

    std::vector<JSEngine::Ref<JSEngine::Mesh>>       m_MeshVec;
    std::vector<JSEngine::Ref<JSEngine::Mesh>>       m_VAOVec;
    std::vector<JSEngine::Ref<JSEngine::Light>>      m_LightVec;

    JSEngine::Ref<JSEngine::SceneData>               m_SceneData;


    JSEngine::Ref<JSEngine::Scene3D> m_Scene;


};