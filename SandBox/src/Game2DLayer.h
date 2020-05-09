#pragma once
#include <JSEngine.h>
#include <vector>

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


};